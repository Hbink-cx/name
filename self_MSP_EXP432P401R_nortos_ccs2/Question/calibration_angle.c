/*
 * calibration_angle.c
 *
 *  Created on: 2023年8月3日
 *      Author: bink
 */
#include "calibration_angle.h"
float mode=0;
calibration_init calibration_init_t;
const calibration_init* get_calibration_info(void)
{
    return &calibration_init_t;
}
void calibration_angle_init()
{
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
       /* Configuring P1.1 as an input and enabling interrupts */
       MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
       MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
       MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
       MAP_Interrupt_enableInterrupt(INT_PORT1);

       /* Enabling SRAM Bank Retention */
       MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
            MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
            MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
//            MAP_Interrupt_enableInterrupt(INT_PORT1);
       MAP_SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1);

       /* Enabling MASTER interrupts */
       MAP_Interrupt_enableMaster();
}

void PORT1_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    /* Toggling the output on the LED */
    if(status & GPIO_PIN1)
   {   int i;
//        if(mode<=4){
//
//
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
        if (mode==0){
            calibration_init_t.mode=1;
        }

//        if(mode==0){
//            calibration_init_t.mode=1;
//            calibration_init_t.center_angle_x =  getAngleFromJY901S() ;//x
//            calibration_init_t.center_angle_z =  getAngle2FromJY901S(); //z
//        }
//        for(i=1;i<5;i++){
//            if(mode==i){
//
//               calibration_init_t.calibration_angle[i-1][0]= getAngleFromJY901S() ;//x
//               calibration_init_t.calibration_angle[i-1][1]=  getAngle2FromJY901S(); //z
//             }
//           }
//        }
//         if(mode>4){
//             calibration_init_t.mode=1;
//             MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);//然后开始到中间去
//         }

    }
    else if(status & GPIO_PIN4)
    {
        calibration_init_t.mode=calibration_init_t.mode+1;
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);//然后停止



    }
    mode=mode+0.5;

}



