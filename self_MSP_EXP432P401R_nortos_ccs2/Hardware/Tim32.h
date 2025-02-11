/*
 * Tim32.h
 *
 *  Created on: 2023Äê7ÔÂ8ÈÕ
 *      Author: bink
 */

#ifndef TIM32_H_
#define TIM32_H_
#include "System\sysinit.h"

uint32_t count_32;
uint32_t key;

void Tim32_0_Int_Init(uint32_t aar, uint8_t psc);
void Tim32_time_0p1s();//0.1Ãë
void Tim32_time_1s();
/* Timer32 ISR */
void T32_INT1_IRQHandler(void);
void Tim32_1_Int_Init(uint32_t aar, uint8_t psc);
void T32_INT2_IRQHandler(void);
void Tim32_showtime();


#endif /* TIM32_H_ */
