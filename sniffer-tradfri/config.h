#ifndef __CONFIG_H__
#define __CONFIG_H__

#define LED_PORT gpioPortC
#define LED_PIN	11

#ifndef LED_PIN
#define LED_PIN     13
#endif
#ifndef LED_PORT
#define LED_PORT    gpioPortB
#endif


#define USART_RX_PORT gpioPortB
#define USART_RX_PIN 14
#define USART_RX_LOCATION USART_ROUTELOC0_RXLOC_LOC8


#define USART_TX_PORT gpioPortB
#define USART_TX_PIN 15
#define USART_TX_LOCATION USART_ROUTELOC0_TXLOC_LOC10

#endif