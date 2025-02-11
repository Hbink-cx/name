/*
 * go_to_center.c
 *
 *  Created on: 2023年8月4日
 *      Author: bink
 */
#include "go_to_center.h"
#include "external_devices\getAngle.h"

float duojipid_1[2][3]=
{{0.01,0,0},{0.1,0,0}};
coordinate coordinate_t;
int go_to_center_mode=0;
void go_to_center_loop()
{ if(go_to_center_mode==0 && getCenterCoordinateDatax()!=0)
{
        coordinate_t.center_x  =   getCenterCoordinateDatax();
        coordinate_t.center_y  =   getCenterCoordinateDatay();
        go_to_center_mode=1;
}
//delay_ms(100);
       coordinate_t.target_x  =   getCoordinateDatax();
       coordinate_t.target_y  =   getCoordinateDatay();
       transimit(306,coordinate_t.target_x, -coordinate_t.duoji_pwm[0]);

//if (coordinate_t.target_x!=0){
        coordinate_t.duoji_pwm[0]+=PID_calc(&coordinate_t.duoji_pid[0],coordinate_t.target_x,306);   //计算设置的值
        coordinate_t.duoji_pwm[1]=PID_calc(&coordinate_t.duoji_pid[1],coordinate_t.target_y,195);
        if(coordinate_t.duoji_pwm[0]>-760)
        {
            coordinate_t.duoji_pwm[0]=-760;
        }
        if(coordinate_t.duoji_pwm[0]<-1100)
        {
            coordinate_t.duoji_pwm[0]=-1000;
        }
        transimit(306,coordinate_t.target_x, -coordinate_t.duoji_pwm[0]);
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,-coordinate_t.duoji_pwm[0]); // 设置值
//          MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,coordinate_t.duoji_pwm[1]);
//}



}

void go_to_center_init()
{
//    TimA1_PWM_Init();
//    TimA1_PWM_Init2();
    duoji_init(1000);
    duoji_init_2(1400);

    PID_init(&coordinate_t.duoji_pid[0], PID_POSITION,  duojipid_1[0], 2500,2500);
    PID_init(&coordinate_t.duoji_pid[1], PID_POSITION, duojipid_1[1],500,500);
    inituart_to_pc(EUSCI_A2_BASE);
    inituart_to_pc(EUSCI_A0_BASE);


    //
//               if(go_center.dx-go_center.dx1<0.3 && go_center.dx-go_center.dx1>-0.3 && go_center.dz-go_center.dz1<0.3 && go_center.dz-go_center.dz1>-0.3 )
//               {
//                   break;
//               }

}

