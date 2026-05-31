/*
 * radio.c
 *
 *  Created on: May 16, 2020
 *      Author: mybays
 */


/*
 * Interface to the EFM32 radio module in IEEE 802.15.4 mode
 */
#include <stdio.h>
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_core.h"
#include "radio.h"
#include "timer.h"
#include "rail.h"
#include "protocol/ieee802154/rail_ieee802154.h"

#ifndef RADIO_CHANNEL
#define RADIO_CHANNEL 11
#endif

uint8_t radio_mac_address[8];
uint16_t radio_short_address = 0xFFFF; // default value
uint16_t radio_pan_id = 0xFFFF; // default value
static bool radio_promiscuous;
static volatile int radio_tx_pending;
static int radio_channel;


typedef enum {
    RADIO_UNINIT,
    RADIO_INITING,
    RADIO_IDLE,
    RADIO_TX,
    RADIO_RX,
    RADIO_CALIBRATION
} siliconlabs_modem_state_t;

static siliconlabs_modem_state_t radio_state = RADIO_UNINIT;

static volatile RAIL_Handle_t rail = NULL;
static void rail_callback_events(RAIL_Handle_t rail, RAIL_Events_t events);

// can't be const since the buffer is used for writes
static RAIL_Config_t rail_config = {
	.eventsCallback		= rail_callback_events,
	.protocol		= NULL, // must be NULL for ieee802.15.4
	.scheduler		= NULL, // not multi-protocol
	.buffer			= {}, // must be zero
};

static const RAIL_DataConfig_t rail_data_config = {
	.txSource = TX_PACKET_DATA,
	.rxSource = RX_PACKET_DATA,
	.txMethod = PACKET_MODE,
	.rxMethod = PACKET_MODE,
};


static const RAIL_IEEE802154_Config_t ieee802154_config = {
	// if zrepl is used for receiving, then promiscuous must be
	// enabled since filtering on multipurpose frames is not supported
	.promiscuousMode	= true,
	.isPanCoordinator	= false,
	.framesMask		= RAIL_IEEE802154_ACCEPT_STANDARD_FRAMES,
	.ackConfig = {
		.enable			= true, // enable autoack
		.ackTimeout		= 54 * 16, // 54 symbols * 16 us/symbol = 864 usec
		.rxTransitions = {
			.success = RAIL_RF_STATE_RX, // go to Tx to send the ACK
			.error = RAIL_RF_STATE_RX, // ignored
		},
		.txTransitions = {
			.success = RAIL_RF_STATE_RX, // go to Rx for receiving the ACK
			.error = RAIL_RF_STATE_RX, // ignored
		},
	},
	.timings = {
		.idleToRx		= 100,
		.idleToTx		= 100,
		.rxToTx			= 192, // 12 symbols * 16 us/symbol
		.txToRx			= 192 - 10, // slightly lower to make sure we get to RX in time
		.rxSearchTimeout	= 0, // not used
		.txToRxSearchTimeout	= 0, // not used
	},
	.addresses		= NULL, // will be set by explicit calls
};

static const RAIL_TxPowerConfig_t paInit2p4 = {
	.mode			= RAIL_TX_POWER_MODE_2P4_HP,
	.voltage		= 1800,
	.rampTime		= 10,
};

static const RAIL_CsmaConfig_t csma_config = RAIL_CSMA_CONFIG_802_15_4_2003_2p4_GHz_OQPSK_CSMA;

/*
 * Called when radio calibration is required
 */
void RAILCb_CalNeeded()
{
	printf("calibrateRadio\n");
	//calibrateRadio = true;
}

static void rail_callback_rfready(RAIL_Handle_t rail)
{
	radio_state = RADIO_IDLE;
	radio_tx_pending = 0;
}

#define MAX_PKTS 4
static volatile unsigned rx_buffer_write;
static volatile unsigned rx_buffer_read;
static uint8_t rx_buffers[MAX_PKTS][MAC_PACKET_MAX_LENGTH];
static uint8_t rx_buffer_copy[MAC_PACKET_MAX_LENGTH];

uint8_t radio_tx_buffer[MAC_PACKET_MAX_LENGTH];

#define FRAME_TYPE_ACK	0x02

/*
 * Send a pre-formed ACK message ASAP in the RX path,
 * using the AutoAckFifo.  Needs to fill in the sequence
 * number from the message, so this is not safe to call from
 * outside the RX interrupt.
 */
static int
radio_tx_autoack(uint8_t seq)
{
	static uint8_t ack_buf[] = {
		0x05,	// length, including FCS
		FRAME_TYPE_ACK,
		0x00,   // FCF bits that we don't care about
		0x00,	// seq goes here
	};

	ack_buf[3] = seq;
	int rc = RAIL_WriteAutoAckFifo(rail, ack_buf, 5);
	printf("ack rc=%d\n", rc);
	return rc;
}


static void process_packet(RAIL_Handle_t rail)
{
	RAIL_RxPacketInfo_t info;
	RAIL_RxPacketHandle_t handle = RAIL_GetRxPacketInfo(rail, RAIL_RX_PACKET_HANDLE_NEWEST, &info);

	// not a valid receive? discard it.
	if (info.packetStatus != RAIL_RX_PACKET_READY_SUCCESS)
		goto done;
	// too long? discard it.
	if (info.packetBytes > MAC_PACKET_MAX_LENGTH)
		goto done;

	// check for an ack packet and turn off the auto ack for this rx
	uint8_t header[4];
	RAIL_PeekRxPacket(rail, handle, header, sizeof(header), 0);
	const uint8_t len = header[0];
	const uint8_t packet_type = header[1] & 0x03;
	const uint8_t ack_requested = header[1] & 0x20;
	if (len == 5 && packet_type == FRAME_TYPE_ACK)
	{
		// this is an ack, so don't send a reply
		RAIL_CancelAutoAck(rail);
		// could check to see if this acks our last packet
		// and not forward it up the stack, but we let it pass for now
		//waiting_for_ack = false;
		//last_ack_pending_bit = (header[1] & (1 << 4)) != 0;
		//printf("got ack\n");
	} else
	if (ack_requested && !radio_promiscuous)
	{
		// ACK requested and to us, assume the sequence number
		// is the third byte in the header (after the length byte,
		// and the two bytes of the FCF).
		radio_tx_autoack(header[3]);
	}

	{
		RAIL_RxPacketDetails_t details;
		details.timeReceived.timePosition = RAIL_PACKET_TIME_DEFAULT;
		details.timeReceived.totalPacketBytes = 0;
		RAIL_GetRxPacketDetails(rail, handle, &details);

		unsigned write_index = rx_buffer_write;
		uint8_t * rx_buffer = rx_buffers[write_index];
		if (info.packetBytes > MAC_PACKET_MAX_LENGTH - 2)
		{
			// should never happen?
			printf("rx too long %d\n", info.packetBytes);
		} else {
			RAIL_CopyRxPacket(rx_buffer, &info); // puts the length in byte 0

			// allow the zrepl to process this message
			// length is in the first byte and includes
			// an extra two bytes at the end that we ignore
			//if (zrepl_recv(rx_buffer+1, *rx_buffer - 2))
			//{
				// consumed by zrepl, do not forward it
			//} else
			if (write_index == MAX_PKTS - 1)
				rx_buffer_write = 0;
			else
				rx_buffer_write = write_index + 1;
		}

/*
		// cancel the ACK if the sender did not request one
		// buffer[0] == length
		// buffer[1] == frame_type[0:2], security[3], frame_pending[4], ack_req[5], intrapan[6]
		// buffer[2] == destmode[2:3], version[4:5], srcmode[6:7]
		if ((rx_buffer[1] & (1 << 5)) == 0)
			RAIL_CancelAutoAck(rail);
*/

#if 1
		printf("rx %2d bytes lqi=%d rssi=%d:", info.packetBytes, details.lqi, details.rssi);

		// skip the length byte
		for(int i = 1 ; i < info.packetBytes ; i++)
		{
			printf(" %02x", rx_buffer[i]);
		}
		printf("\r\n");
#endif
	}

done:
	RAIL_ReleaseRxPacket(rail, handle);
}


/*
 * Callbank from the radio interrupt when there is an event.
 * rx 00000000:00018030
 */

static void rail_callback_events(RAIL_Handle_t rail, RAIL_Events_t events)
{
	if(1)
	{
		// ignore certain bit patterns unless other things are set
		events &= ~( 0
			| RAIL_EVENT_RX_PREAMBLE_LOST
			| RAIL_EVENT_RX_PREAMBLE_DETECT
			| RAIL_EVENT_RX_TIMING_LOST
			| RAIL_EVENT_RX_TIMING_DETECT
		);

		if(events == 0)
			return;

		printf("rx %08x:%08x\r\n",
			(unsigned int)(events >> 32),
			(unsigned int)(events >> 0));
	}

	if (events & RAIL_EVENT_RSSI_AVERAGE_DONE)
	{
		printf("rssi %d\r\n", RAIL_GetAverageRssi(rail));
	}

	if (events & RAIL_EVENT_RX_ACK_TIMEOUT)
	{
		//
	}

	if (events & RAIL_EVENT_RX_PACKET_RECEIVED)
	{
	    printf("process_packet\r\n");
		process_packet(rail);
	}

	if (events & RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND)
	{
           /*
            * Indicates a Data Request is being received when using IEEE 802.15.4
            * functionality. This occurs when the command byte of an incoming frame is
            * for a data request, which requests an ACK. This callback is called before
            * the packet is fully received to allow the node to have more time to decide
            * whether to set the frame pending in the outgoing ACK. This event only ever
            * occurs if the RAIL IEEE 802.15.4 functionality is enabled.
            *
            * Call \ref RAIL_IEEE802154_GetAddress to get the source address of the
            * packet.
            */
	}

	if (events & RAIL_EVENTS_TX_COMPLETION)
	{
		// they are done with our packet, either for good or worse
		//printf("TX done!\n");
		radio_tx_pending = 0;
	}

	if (events & RAIL_EVENT_CAL_NEEDED)
	{
		// we should flag that a calibration is needed
		// does this cancel any transmits?
		radio_tx_pending = 0;
	}

	// lots of other events that we don't handle
}

static void radio_channel_set(unsigned channel)
{
	RAIL_Idle(rail, RAIL_IDLE_FORCE_SHUTDOWN_CLEAR_FLAGS, true);
	radio_state = RADIO_RX;
	radio_channel = channel;
	RAIL_StartRx(rail, channel, NULL);
}

void set_channel(int channel)
{
    radio_channel_set(channel);
}

void radio_init(void)
{
	// do not re-init
	if (radio_state != RADIO_UNINIT)
		return;


	if(1)
	{
		RAIL_Version_t version;
		RAIL_GetVersion(&version, true);
		printf("mac=%08x:%08x",
			(unsigned int) DEVINFO->UNIQUEH,
			(unsigned int) DEVINFO->UNIQUEL
		);

		printf(" rail=%d.%d-%d build %d flags %d (%08x)%s\r\n",
			version.major,
			version.minor,
			version.rev,
			version.build,
			version.flags,
			(unsigned int) version.hash,
			version.multiprotocol ? " multiprotocol" : ""
		);
	}
	rail = RAIL_Init(&rail_config, rail_callback_rfready);
	RAIL_ConfigData(rail, &rail_data_config);
	RAIL_ConfigCal(rail, RAIL_CAL_ALL);
	RAIL_IEEE802154_Config2p4GHzRadio(rail);
	RAIL_IEEE802154_Init(rail, &ieee802154_config);
	RAIL_ConfigEvents(rail, RAIL_EVENTS_ALL, 0
		| RAIL_EVENT_RSSI_AVERAGE_DONE
		| RAIL_EVENT_RX_ACK_TIMEOUT
		| RAIL_EVENT_RX_PACKET_RECEIVED
		| RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
		| RAIL_EVENTS_TX_COMPLETION
		| RAIL_EVENTS_TXACK_COMPLETION
		| RAIL_EVENT_CAL_NEEDED
	);
	RAIL_ConfigTxPower(rail, &paInit2p4);
	RAIL_SetTxPower(rail, 255); // max
	// use the device unique id as the mac for network index 0
	memcpy(&radio_mac_address[0], (const void*)&DEVINFO->UNIQUEL, 4);
	memcpy(&radio_mac_address[4], (const void*)&DEVINFO->UNIQUEH, 4);
	RAIL_IEEE802154_SetLongAddress(rail, radio_mac_address, 0);
	// set the short address to something other than 0
	RAIL_IEEE802154_SetShortAddress(rail, radio_short_address, 0);
	RAIL_IEEE802154_SetPanId(rail, radio_pan_id, 0);
	// unpause auto-ack
	RAIL_PauseRxAutoAck(rail, false);

	// cache the current promiscuous mode
	radio_promiscuous = ieee802154_config.promiscuousMode;

	radio_channel_set(RADIO_CHANNEL);
	printf("radio init finished.\r\n");
}


void * radio_tx_buffer_get(unsigned usec_delay)
{
	unsigned delay = 0;

	// if we don't get a packet after a while, assume that
	// something has hung and return the packet anyway
	// should flag this
	while(radio_tx_pending)
	{
		if (delay >= usec_delay)
		{
			printf("tx stall\n");
			break;
		}

		_delay_us(100);
		delay += 100;
	}

	return &radio_tx_buffer[1];
}


// length of message should be in radio_tx_buffer[0]
// returns 0 if ok, non-zero if not
int radio_tx_buffer_send(size_t len)
{
	// radio tx length including the 2 byte FCS at the end
	*(volatile uint8_t*) &radio_tx_buffer[0] = 2 + len;

	CORE_ATOMIC_IRQ_DISABLE();

	radio_tx_pending = 1;
	radio_state = RADIO_TX;

	// do we have to quiese the radio here?
	//RAIL_Idle(rail, RAIL_IDLE_ABORT, true);

	RAIL_SetTxFifo(rail, radio_tx_buffer, len + 1, len + 1);
	RAIL_TxOptions_t txOpt = RAIL_TX_OPTIONS_DEFAULT;
	printf("%s done\r\n",__FUNCTION__);

/*
	// check if we're waiting for an ack, but not yet implemented
	// also doesn't work for multipurpose frames
	if (radio_tx_buffer[1+1] & (1 << 5))
		txOpt |= RAIL_TX_OPTION_WAIT_FOR_ACK;
*/

	// start the transmit, we hope!
	int rc = RAIL_StartCcaCsmaTx(
		rail,
		radio_channel,
		txOpt,
		&csma_config,
		NULL
	);

	// if it failed to start, unset the pending flag
	if (rc != 0)
		radio_tx_pending = 0;

	CORE_ATOMIC_IRQ_ENABLE();

	return rc;
}


int zrepl_active;
// hook the uart print function and send 802.15.4 messages
static uint8_t zrepl_seq = 0;

void ieee802154_send(const char * str, size_t len)
{
	if (!zrepl_active)
		return;
	printf("%s\r\n",__FUNCTION__);
	// turn it off for now
	zrepl_active = 0;

	while(len)
	{
		// wait up to 10 ms for any existing packets to go out
		// if there is a tx in process, we don't want to interfere
		// with the transfer.
		zrepl_packet_t * const msg = radio_tx_buffer_get(100000);
		if (!msg)
			break;

		// fill in the header
		msg->fcf = ZREPL_FCF_SEND;
		msg->seq = zrepl_seq++;
		memcpy(msg->mac, radio_mac_address, sizeof(msg->mac));

		const size_t max_data_len = 60 - sizeof(*msg);
		size_t data_len = len;
		if (data_len > max_data_len)
			data_len = max_data_len;

		// fill in the buffer, up to the length
		memcpy(msg->data, str, data_len);
		len -= data_len;
		str += data_len;

		// and put it on the wire; abort if there is a failure
		if (radio_tx_buffer_send(sizeof(*msg) + data_len) != 0)
			; // return;
	}

	// turn it back on
	zrepl_active = 1;
}
int ieee802154_recv(const void * msg, size_t len)
{
	return 0;
}
