/*
 * spi.c
 *
 *  Created on: May 10, 2020
 *      Author: mybays
 */

#include "stdio.h"

#include "em_device.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "spi.h"

int spiTest()
{


	uint8_t TxBuffer[TX_BUFFER_SIZE] = {0x9F, 0x00, 0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
	//uint32_t TxBufferIndex = 0;

	uint8_t RxBuffer[RX_BUFFER_SIZE] = {0};
	//uint32_t RxBufferIndex = 0;

	GPIO_PinOutClear(SPI_CS_PORT, SPI_CS_PIN);
	for(int i=0;i<4;i++)
	{
		RxBuffer[i]=USART_SpiTransfer(USART1, TxBuffer[i]);
	}
	GPIO_PinOutSet(SPI_CS_PORT, SPI_CS_PIN);
	printf("JEDEC ID: %x %x %x.\r\n",RxBuffer[1],RxBuffer[2],RxBuffer[3]);
	return 0;
}
