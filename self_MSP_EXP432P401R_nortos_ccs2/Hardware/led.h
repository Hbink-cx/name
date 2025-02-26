/*
 * led.h
 *
 *  Created on: 2023年7月8日
 *      Author: bink
 */

#ifndef __LED_H
#define __LED_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// 位带操作
#define LED_RED BITBAND_PERI(P1OUT,0)
#define LED_R BITBAND_PERI(P2OUT,0)
#define LED_G BITBAND_PERI(P2OUT,1)
#define LED_B BITBAND_PERI(P2OUT,2)

void LED_Init(void);

void LED_RED_On(void);
void LED_RED_Off(void);
void LED_RED_Tog(void);

void LED_Y_On(void);
void LED_C_On(void);
void LED_P_On(void);

void LED_R_On(void);
void LED_G_On(void);
void LED_B_On(void);

void LED_R_Off(void);
void LED_G_Off(void);
void LED_B_Off(void);

void LED_R_Tog(void);
void LED_G_Tog(void);
void LED_B_Tog(void);

void LED_W_On(void);
void LED_W_Off(void);
void LED_W_Tog(void);

void LED_Show_Staus(uint8_t num);
#endif
