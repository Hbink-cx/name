/*
 * duoji.c
 *
 *  Created on: 2023年7月30日
 *      Author: bink
 */

//
////1.配置GPIO复用
#include "duoji.h"
void duoji_init(uint32_t ccr1)
{
//GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7,GPIO_PIN7,GPIO_PRIMARY_MODULE_FUNCTION);
MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
Timer_A_PWMConfig TimA1_PWMConfig;
TimA1_PWMConfig.clockSource=TIMER_A_CLOCKSOURCE_SMCLK;
TimA1_PWMConfig.clockSourceDivider=12;      //smlk12mhz 搞12分频
TimA1_PWMConfig.timerPeriod=20000;          //配置一个50hz 的频率
TimA1_PWMConfig.compareRegister=TIMER_A_CAPTURECOMPARE_REGISTER_1;
TimA1_PWMConfig.compareOutputMode=TIMER_A_OUTPUTMODE_TOGGLE_SET;
TimA1_PWMConfig.dutyCycle=ccr1;
Timer_A_generatePWM(TIMER_A1_BASE,&TimA1_PWMConfig);
}
void duoji_init_2(uint32_t ccr1)
{
//GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7,GPIO_PIN7,GPIO_PRIMARY_MODULE_FUNCTION);
MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
Timer_A_PWMConfig TimA1_PWMConfig1;
TimA1_PWMConfig1.clockSource=TIMER_A_CLOCKSOURCE_SMCLK;
TimA1_PWMConfig1.clockSourceDivider=12;      //smlk12mhz 搞12分频
TimA1_PWMConfig1.timerPeriod=20000;          //配置一个50hz 的频率
TimA1_PWMConfig1.compareRegister=TIMER_A_CAPTURECOMPARE_REGISTER_3;
TimA1_PWMConfig1.compareOutputMode=TIMER_A_OUTPUTMODE_TOGGLE_SET;
TimA1_PWMConfig1.dutyCycle=ccr1;
Timer_A_generatePWM(TIMER_A1_BASE,&TimA1_PWMConfig1);
}
