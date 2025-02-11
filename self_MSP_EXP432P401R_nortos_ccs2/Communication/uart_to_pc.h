/*
 * uart_to_pc.h
 *
 *  Created on: 2023��7��5��
 *      Author: 32753
 */

#ifndef UART_TO_PC_H_
#define UART_TO_PC_H_
#include"System\sysinit.h"
#include"ALL.h"
void inituart_to_pc(uint32_t moduleInstance);
void EUSCIA0_IRQHandler(void );
void EUSCIA1_IRQHandler(void );
void EUSCIA2_IRQHandler(void );
void EUSCIA3_IRQHandler(void );
void uart_test();
//extern uint8_t endflag[4];
#endif /* UART_TO_PC_H_ */
