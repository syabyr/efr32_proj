/*
 * radio.h
 *
 *  Created on: May 16, 2020
 *      Author: mybays
 */

#ifndef INC_RADIO_H_
#define INC_RADIO_H_

/* 802.15.4 maximum size of a single packet including PHY byte is 128 bytes
 * but we don't support that */
#define MAC_PACKET_MAX_LENGTH   128
/* Offsets of prepended data in packet buffer */
#define MAC_PACKET_OFFSET_RSSI  0
#define MAC_PACKET_OFFSET_LQI   1
/* This driver prepends RSSI and LQI */
#define MAC_PACKET_INFO_LENGTH  2

extern void radio_init(void);

extern uint8_t radio_mac_address[8];


extern int zrepl_active;

// "Multipurpose" frames are used (type 5), which have the minimum amount of
// overhead.  There are two valid Frame Control Fields (FCF), one
// for zrepl sends and one for zrepl receives.
#define ZREPL_FCF_SEND	(0 \
	| 5 << 0 /* Multipurpose frame */ \
	| 0 << 3 /* Short frame type */ \
	| 0 << 4 /* No dest address is present */ \
	| 3 << 6 /* Long source address is present */ \
	)

#define ZREPL_FCF_RECV	(0 \
	| 5 << 0 /* Multipurpose frame */ \
	| 0 << 3 /* Short frame type */ \
	| 3 << 4 /* Long dest address is present */ \
	| 0 << 6 /* No source address is present */ \
	)

typedef struct
{
	uint8_t fcf;
	uint8_t seq;
	uint8_t mac[8];
	uint8_t data[];
} zrepl_packet_t;


extern void * radio_tx_buffer_get(unsigned usec_delay);
extern int radio_tx_buffer_send(size_t len);


void ieee802154_send(const char * str, size_t len);
int ieee802154_recv(const void * msg, size_t len);

#endif /* INC_RADIO_H_ */
