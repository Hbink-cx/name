
/* Standard Includes */
//#include"System\sysinit.h"
//#include <stdio.h>
//#include "external_devices\oled.h"
//#include "external_devices\fmq.h"
//#include "external_devices\motor.h"
//#include "Hardware\timA.h"
//#include "algorithm\pid.h"
//#include "Hardware\Tim32.h"
//#include "Communication\uart_to_pc.h"
//#include "hardware\led.h"
//#include "Communication\vofa.h"
#include "ALL.h"
#include "external_devices\getAngle.h"
#include "Question\Question.h"
int32_t set_speed1[2]={200,200};

uint32_t speedCount = 0;
float speed = 0;
#include <stdio.h>
pid_type_def duoji_pid[2];
int duoji_pwm[2];
//float duojipid[2][3]=
//{{0.01,0.001,0.001},{6,0.03,0}};
//float duojipid[2][3]=
//{{0.1,0.01,0.001},{6,0.03,0}};
float duojipid[2][3]=
{{3,0.013,0},{4,0.007,0}};
float dx;
float dz;
float dy;
float dx1;
float dz1;

int main(void){
    SysInit();
    delay_init();//这两个初始化必须放
    LED_Init();
    OLED_Init();
    MAP_FPU_enableModule();
    motor_init();

    inituart_to_pc(EUSCI_A0_BASE);
    inituart_to_pc(EUSCI_A3_BASE);
    inituart_to_pc(EUSCI_A2_BASE);
    inituart_to_pc(EUSCI_A1_BASE);

    calibration_angle_init();
    const calibration_init* calibration= get_calibration_info();

//    go_center_Init();

    go_to_center_init();
//    PID_init(&duoji_pid[0], PID_POSITION, duojipid[0], 1000,1000);
//    PID_init(&duoji_pid[1], PID_POSITION, duojipid[1], 900,900);
//    MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,1000);
//    MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,1700);
    delay_s(3);
//    delay_s(10);
//
int follow_mode=0;
int i=0;
    while(1){

        if(calibration->mode==1)
        {
            if(follow_mode==0){
            go_to_center_init();
            follow_mode=1;

        }


            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,885);//中心
                                       delay_s(1);
            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,745);//
                                    delay_s(1);
        }

        else if(calibration->mode==2)
        {
//            go_to_center_init();
            for(i=0;i<210;i++)
            {

                        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,1000-i);//左上角
                                                   delay_ms(20);
                                                   if (i==20)
                                                   {
                                                       MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,832);
                                                                                                 delay_ms(20);
                                                   }



            }
    //            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,813);//右上角
    //                                       delay_s(1);
    //            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,835);
    //                                    delay_s(1);

               for(i=0;i<190;i++)
               {
                   MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,790);//左上角
                                                          delay_ms(20);
                               MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,822-i);
                                                       delay_ms(20);

               }
               for(i=0;i<176;i++)
                         {
                             MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,813+i);//左上角
                                                                    delay_ms(20);
                                        if(i==50){
                                            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,639);
                                                                                             delay_ms(20);
                                        }


                         }
               for(i=0;i<215;i++)
                                    {
                                        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,993);//左上角
                                                                               delay_ms(20);

                                                       MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,629+i);
                                                                                                        delay_ms(20);



                                    }
        }
        else if (calibration->mode>=3)
        {

            go_to_center_init();
            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,790);//中心
                                       delay_s(1);
            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,645);//
            delay_s(1);
            for(i=0;i<115;i++)
             {
                 MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,790+i);//左上角
                                        delay_ms(20);

                MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,645);
                                         delay_ms(20);

            }
            for(i=0;i<83;i++)
             {   MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,905);//左上角
                                        delay_ms(20);
                MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,645+i);
                                         delay_ms(20);
            }
            for(i=0;i<115;i++)
             {
                 MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,905-i);//左上角
                                        delay_ms(20);
                                        if(i==45){
                MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,709);
                                         delay_ms(20);
                                        }
                                        }
            for(i=0;i<83;i++)
                         {
                             MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,790);//左上角
                                                    delay_ms(20);

                            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,709-i);
                                                     delay_ms(20);

                                                    }

        }


//            for(i=500;i<1500;){
//                i=i+100;
//                MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,i);
//                           delay_s(1);
////               MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,i);
////               delay_s(1);
//               transimit(i, 0, 0);
//            }
//            for(i=500;i<1500;){
//                       i=i+100;
//                       MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,i);
//                                  delay_s(1);
//       //               MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,i);
//       //               delay_s(1);
//                      transimit(i, 0, 0);
//                   }
//        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,856);
//                                   delay_s(1);
//        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,749);
//                                delay_s(1);
//        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,890);//中心
//                                   delay_s(1);
//        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,747);//
//                                delay_s(1);
//        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,1000);//左上角
//                                   delay_s(1);
//        MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,832);
//                                delay_s(1);
//
//

       //go_to_center_loop();

//        for(i=0;i<95;i++)
//         {
//             MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,790);//左上角
//                                    delay_ms(20);
//            MAP_Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,727-i);
//                                     delay_ms(20);
//        }


    }
}
