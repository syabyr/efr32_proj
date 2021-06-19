/*
 * uart0.h
 *
 *  Created on: May 15, 2020
 *      Author: mybays
 */

#ifndef INC_UART0_H_
#define INC_UART0_H_


#include "config.h"

#ifndef USART_TX_PORT
#define USART_TX_PORT gpioPortB
#endif

#ifndef USART_TX_PIN
#define USART_TX_PIN 15
#endif

#ifndef USART_TX_LOCATION
#define USART_TX_LOCATION 10 // ? found in af_pins.h somehow
#endif

#ifndef USART_RX_PORT
#define USART_RX_PORT gpioPortB
#endif

#ifndef USART_RX_PIN
#define USART_RX_PIN 14
#endif

#ifndef USART_RX_LOCATION
#define USART_RX_LOCATION 8 // ?
#endif

void initUart0();
void USART0_enter_DefaultMode_from_RESET(void);

#endif /* INC_UART0_H_ */
