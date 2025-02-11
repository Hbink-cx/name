/*
 * go_center.c
 *
 *  Created on: 2023年8月3日
 *      Author: Emma
 */
#include "go_center.h"
#include "external_devices/external_devices.h"
#include "algorithm/pid.h"
#include "Communication/Communication.h"
#include "external_devices\duoji.h"
go_center_t go_center;
float duojipid_0[2][3]=
{{3,0.013,0},{4,0.007,0}};
void go_center_Init()
{
//    TimA1_PWM_Init();
//    TimA1_PWM_Init2();
    duoji_init(0);
    duoji_init_2(0);

    PID_init(&go_center.duoji_pid[0], PID_POSITION, duojipid_0[0], 1000,1000);
    PID_init(&go_center.duoji_pid[1], PID_POSITION, duojipid_0[1], 500,500);
    inituart_to_pc(EUSCI_A2_BASE);
    inituart_to_pc(EUSCI_A0_BASE);
    const calibration_init* calibration1= get_calibration_info();
    go_center.dx1=calibration1->center_angle_x;
    go_center.dz1=calibration1->center_angle_z;
}
void go_center_loop()
{
    go_center_Init();
//    go_center.dx=getAngleFromJY901S()-go_center.dx1;//
//    go_center.dz=900-getAngle2FromJY901S()+go_center.dz1;
//    go_center.duoji_pwm[0]=PID_calc(&go_center.duoji_pid[0],go_center.dx,0);
//    go_center.duoji_pwm[1]=PID_calc(&go_center.duoji_pid[1],go_center.dz,0);
////    MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,1500+go_center.duoji_pwm[0]);
////    MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,900-go_center.duoji_pwm[1]);
//    delay_ms(20);
        while(1)
        {

            go_center.dx=getAngleFromJY901S();//
            go_center.dz=getAngle2FromJY901S();

            go_center.duoji_pwm[0]=PID_calc(&go_center.duoji_pid[0],go_center.dx,go_center.dx1);   //计算设置的值
            go_center.duoji_pwm[1]=PID_calc(&go_center.duoji_pid[1],go_center.dz,go_center.dz1);


            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,1500-go_center.duoji_pwm[0]); // 设置值
            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,1400+go_center.duoji_pwm[1]);
 //
            if(go_center.dx-go_center.dx1<0.3 && go_center.dx-go_center.dx1>-0.3 && go_center.dz-go_center.dz1<0.3 && go_center.dz-go_center.dz1>-0.3 )
            {
                break;
            }

        }
}


const go_center_t* get_go_center_info(void)
{
    return &go_center;
}

