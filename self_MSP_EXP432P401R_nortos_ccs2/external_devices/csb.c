/*
 * csb.c
 *超声波模块
 *Trig:p5.1   (普通io口)
 *Echo:p5.5
 * 目前问题：不太准确，合理怀疑是timer设置可以适当延长时间
 *  Created on: 2023年7月8日
 *      Author: bink
 */

#include "csb.h"
#include "external_devices\oled.h"
const Timer_A_UpModeConfig upConfig_csb =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_12,          // SMCLK/1 = 3MHz
        50000,                           // 5000 tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};
void TimA1_csb_Init(void)
{

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN1);//普通引脚
    MAP_GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN5);

    MAP_GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P5, GPIO_PIN5);

    MAP_GPIO_disableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
    MAP_GPIO_disableInterrupt(GPIO_PORT_P5, GPIO_PIN5);

    MAP_Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig_csb);
//    MAP_Interrupt_enableInterrupt(INT_TA1_0);
    MAP_Interrupt_enableSleepOnIsrExit();

    MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);

    MAP_Interrupt_enableMaster();

}
float csb_Distance(void)
{
    int count=0,i=0,sum=0;
    float distance=0;
    while(i!=100)
    {
     GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);//上拉
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);//上拉
        delay_us(10);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);//上拉
//        TIMER_A_CMSIS(TIMER_A1_BASE)->R = 0;
        while(GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN5) == 0);  //
        TIMER_A_CMSIS(TIMER_A1_BASE)->R = 0;
        while(GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN5) == 1);  //
        count=TIMER_A_CMSIS(TIMER_A1_BASE)->R;
        //v = 340m/s = 34000cm/s = 34000cm/10^6us = 0.034cm/us
        //s = vt/2 = t*0.034/2 = t*0.017 ?t/58
        distance=((float)count *10/ 58);//1.0版本线性修订 *0.6
        i++;
        sum=sum+distance;

    }
//    OLED_ShowNum(0, 0, sum/100, 4, 8);
    return sum/100-90;
}
//void TA1_0_IRQHandler(void)
//{
//
//    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
////  Timer_A_getCounterValue(uint32_t timer);
//
//}

