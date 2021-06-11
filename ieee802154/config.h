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

#endif