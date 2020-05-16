/*
 * uart0.h
 *
 *  Created on: May 15, 2020
 *      Author: mybays
 */

#ifndef INC_UART0_H_
#define INC_UART0_H_


#define USART_TX_PORT gpioPortB
#define USART_TX_PIN 15
#define USART_TX_LOCATION 10 // ? found in af_pins.h somehow
#define USART_RX_PORT gpioPortB
#define USART_RX_PIN 14
#define USART_RX_LOCATION 8 // ?


void initUart0();
void USART0_enter_DefaultMode_from_RESET(void);

#endif /* INC_UART0_H_ */
