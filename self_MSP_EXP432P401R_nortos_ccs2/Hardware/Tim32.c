/*
 * Tim32.c
 *ʹ��˵�������Լ�¼ʱ��
 *  Created on: 2023��7��8��
 *      Author: bink
 */
#include "Tim32.h"
#include "external_devices\oled.h"
#include"hardware\led.h"
//#include "motor.h"
//#include"external_devices\fmq.h"
void Tim32_0_Int_Init(uint32_t aar, uint8_t psc)
{
    MAP_Timer32_initModule(TIMER32_0_BASE, psc, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    MAP_Timer32_setCount(TIMER32_0_BASE, aar);
    MAP_Timer32_enableInterrupt(TIMER32_0_BASE);
    MAP_Timer32_startTimer(TIMER32_0_BASE, false); //��������ģʽ false
    MAP_Interrupt_enableInterrupt(INT_T32_INT1);
}
void Tim32_time_0p1s()
{
    Tim32_0_Int_Init(4800000,1);
    MAP_Timer32_startTimer(TIMER32_0_BASE, true);
    key=0;
}
void Tim32_time_1s()
{
    Tim32_0_Int_Init(48000000,1);
    //MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);
    MAP_Timer32_startTimer(TIMER32_0_BASE, true);
    key=1;
}
/* Timer32 ISR */
void T32_INT1_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE);
    count_32++;
    if(count_32%20==0){
        LED_G_Tog();
    }
    if(key==1){
        Tim32_0_Int_Init(48000000,1);
        MAP_Timer32_startTimer(TIMER32_0_BASE, true);
    }
    else if(key==0){
        Tim32_0_Int_Init(4800000,1);
         MAP_Timer32_startTimer(TIMER32_0_BASE, true);
    }
    else if(key=2){
        Tim32_0_Int_Init(480000,1);//10ms处理一次数据
        MAP_Timer32_startTimer(TIMER32_0_BASE, true);
    }



}
void Tim32_showtime(){
    if(key==0){
        OLED_ShowNum(4, 5, count_32/10, 4, 8);
        OLED_ShowString(32, 5, ".", 8);
       OLED_ShowNum(40, 5, count_32%10, 1, 8);
       OLED_ShowString(48, 5, "S", 8);
    }
    else if(key==1){
        OLED_ShowNum(40, 5, count_32, 3, 8);
    }
}



void Tim32_1_Int_Init(uint32_t aar, uint8_t psc)
{
    MAP_Timer32_initModule(TIMER32_1_BASE, psc, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    MAP_Timer32_setCount(TIMER32_1_BASE, aar);
    MAP_Timer32_enableInterrupt(TIMER32_1_BASE);
    MAP_Timer32_startTimer(TIMER32_1_BASE, false); //��������ģʽ false
    MAP_Interrupt_enableInterrupt(INT_T32_INT2);
}

/* Timer32 ISR */
void T32_INT2_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag(TIMER32_1_BASE);

    /*��ʼ����û�����*/

    /*��������û�����*/
}




