/*
 * delay.h
 *
 *  Created on: 2023Äê7ÔÂ7ÈÕ
 *      Author: bink
 */

#ifndef __DELAY_H
#define __DELAY_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void delay_init(void);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
void delay_s(uint32_t ns);
#endif
