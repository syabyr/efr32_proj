/*
 * gpcrc.h
 *
 *  Created on: May 11, 2020
 *      Author: mybays
 */

#ifndef INC_GPCRC_H_
#define INC_GPCRC_H_

#include "em_gpcrc.h"

#define WIDTH       (8 * sizeof(crc_t))
#define TOPBIT      (1 << (WIDTH - 1))
#define POLYNOMIAL  0x04C11DB7
#define PRESET      0xFFFFFFFF

#define ARRAY_SIZE  16
#define STRIDE      0xABCD

typedef uint32_t crc_t;

void initGpcrc(void);
void initSoft(void);
crc_t softCrc(crc_t message, crc_t preset);
void testCrc(void);


#endif /* INC_GPCRC_H_ */
