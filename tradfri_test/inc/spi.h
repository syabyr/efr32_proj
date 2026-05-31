/*
 * spi.h
 *
 *  Created on: May 10, 2020
 *      Author: mybays
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_


#define SPI_CS_PORT gpioPortB
#define SPI_CS_PIN	11


//SPI test
#define TX_BUFFER_SIZE   10
#define RX_BUFFER_SIZE   TX_BUFFER_SIZE



int spiTest();


#endif /* INC_SPI_H_ */
