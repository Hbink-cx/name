/*
 * timA.h
 *
 *  Created on: 2023年7月7日
 *      Author: bink
 */

#ifndef TIMA_H_
#define TIMA_H_

#include "System\sysinit.h"
//#include "motor.h"

//const Timer_A_UpModeConfig upConfig_csb_0;
extern uint8_t TIMA2_CAP_STA;
extern uint16_t TIMA2_CAP_VAL;

//const motor_t* get_motor_info(void);
void TimA0_Int_Init(uint16_t ccr0, uint16_t psc);
void TA0_0_IRQHandler(void);
//void TimA1_PWM_Init(uint16_t ccr0, uint16_t psc);
//void TimA1_csb_Init(void);
void TimA2_Cap_Init(void);
//void TimA2_Int_Init(void);
//void TA2_0_IRQHandler(void);
void TA2_N_IRQHandler(void);
//void TimA3_coder_init(void);    //编码器初始化
//void TA3_0_IRQHandler(void);
//void TA3_N_IRQHandler(void);
#endif
