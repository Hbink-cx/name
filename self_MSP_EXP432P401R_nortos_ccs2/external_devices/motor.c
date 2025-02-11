/*
 * motor.c
 * mg310电机所用的msp432 P2.7引脚有问题，更换为P2.5
 * 其余主控没问题
 * 四倍频
 *  Created on: 2023
 *      Author: bink,Emma
 */


#include "motor.h"
#include "external_devices\oled.h"
//#define PI 3.1415926535
//#define MOTOR_PSC   12              //
//#define MOTOR_CCR0  100     //
//#define MOTOR_PERIMETER  (4.8*PI)   //
//#define MOTOR_RADIUS  2.4
//#define CYCLE_TURNS 390         //
//#define TA2_FREQ    100             //测频法频率


//PID初始化
float opid[2][3]={{3,0,1},
                  {3,0,0}};
//PID速度环
float ipid[2][3]={{40,2.5,1},
                  {40,2.5,0}};//PID系数
//PID速度环
float pid[2][3]={{20,2.1,0}, //20 2 0
                 {20,2.1,0}};//PID系数及时性要高
uint8_t i;//电机驱动
int32_t set_speed_0[2]={0,0};
pid_type_def pwm_pid[2];
int wheel_pwm[2];
motor_t motor;
/******************* 接口 *****************************/
const motor_t* get_motor_info(void)
{
    return &motor;
}
/************************************************/

void TimA2_Int_Init(void)
{
    Timer_A_UpModeConfig upConfig;
    upConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                                      //
    upConfig.clockSourceDivider = 12;                                                      //
    upConfig.timerPeriod = 1000000/TA2_FREQ;                                               //
    upConfig.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;                   //
    upConfig.captureCompareInterruptEnable_CCR0_CCIE =TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE; //
    upConfig.timerClear = TIMER_A_DO_CLEAR;                                                // Clear value

    MAP_Timer_A_configureUpMode(TIMER_A2_BASE, &upConfig);
    MAP_Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    MAP_Interrupt_enableInterrupt(INT_TA2_0);
}

void TA2_0_IRQHandler(void)//仅计算motor内的量
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    BITBAND_PERI(TIMER_A_CMSIS(TIMER_A2_BASE)->CCTL[0], TIMER_A_CCTLN_COV_OFS) = 0;
    motor.speed[0] = motor.turns[0]*TA2_FREQ*MOTOR_PERIMETER/(CYCLE_TURNS*4);
    motor.speed[1] = motor.turns[1]*TA2_FREQ*MOTOR_PERIMETER/(CYCLE_TURNS*4);//需要考虑编码器实际转一圈读取的数据来修正
    motor.abs_distance[0]+= motor.speed[0]*0.01;
        motor.abs_distance[1]+= motor.speed[1]*0.01;
    motor.distance[0]+= motor.speed[0]*0.01;
    motor.distance[1]+= motor.speed[1]*0.01;

    motor.turns[0]=0;
    motor.turns[1]=0;

}
void TimA3_coder_init(void)    //
{
    //a，b相作为输入
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN2 , GPIO_PRIMARY_MODULE_FUNCTION);
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P10, GPIO_PIN4 , GPIO_PRIMARY_MODULE_FUNCTION);
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN2 , GPIO_PRIMARY_MODULE_FUNCTION);
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P10, GPIO_PIN5 , GPIO_PRIMARY_MODULE_FUNCTION);

    Timer_A_ContinuousModeConfig continuousModeConfig = {
         TIMER_A_CLOCKSOURCE_SMCLK,      // SMCLK Clock Source
         TIMER_A_CLOCKSOURCE_DIVIDER_12, // SMCLK/48 = 1MHz
         TIMER_A_TAIE_INTERRUPT_DISABLE,  //
         TIMER_A_DO_CLEAR                // Clear Counter
     };

     MAP_Timer_A_configureContinuousMode(TIMER_A3_BASE, &continuousModeConfig);

 //持续捕获上升沿
     Timer_A_CaptureModeConfig captureModeConfig_TA3 = {
         TIMER_A_CAPTURECOMPARE_REGISTER_0,           //TA3_010.4
         TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE,             //上升沿捕获//1.0上升下降沿捕获
         TIMER_A_CAPTURE_INPUTSELECT_CCIxA,           //
         TIMER_A_CAPTURE_SYNCHRONOUS,                 //同步捕获
         TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,     //
         TIMER_A_OUTPUTMODE_OUTBITVALUE               //输出位置
     };

     MAP_Timer_A_initCapture(TIMER_A3_BASE, &captureModeConfig_TA3);
     captureModeConfig_TA3.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;//10.5
     MAP_Timer_A_initCapture(TIMER_A3_BASE, &captureModeConfig_TA3);
     captureModeConfig_TA3.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;//8.2
     MAP_Timer_A_initCapture(TIMER_A3_BASE, &captureModeConfig_TA3);
     captureModeConfig_TA3.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;//9.2
     MAP_Timer_A_initCapture(TIMER_A3_BASE, &captureModeConfig_TA3);
//四个捕获模式初始化
     MAP_Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_CONTINUOUS_MODE);

     MAP_Timer_A_clearInterruptFlag(TIMER_A3_BASE);
     MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
     MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
     MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
     MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3);

     MAP_Interrupt_enableInterrupt(INT_TA3_N);
     MAP_Interrupt_enableInterrupt(INT_TA3_0);

}


void TA3_0_IRQHandler(void)
{
    if(MAP_Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0))
    {
        MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
        BITBAND_PERI(TIMER_A_CMSIS(TIMER_A3_BASE)->CCTL[0], TIMER_A_CCTLN_COV_OFS) = 0;
    motor.abs_turns[0]++;
        if( GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==1 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==1)
        {
            motor.turns[0]--;
        }
        else if(GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==0 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==1)
        {
            motor.turns[0]++;
        }//这两个是上升沿捕获
        else if(GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==1 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==0)
        {
            motor.turns[0]++;
        }
        else if(GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==0 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==0)
        {
            motor.turns[0]--;
        }//这两个是下降沿捕获
    }
}

/*
 * 10.5
 * 8.2
 * 9.2
 * 的捕获中断都在这里
 */
void TA3_N_IRQHandler(void)
{   //8.2的捕获中断
    if (MAP_Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2))
    {
            MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
            BITBAND_PERI(TIMER_A_CMSIS(TIMER_A3_BASE)->CCTL[2], TIMER_A_CCTLN_COV_OFS) = 0;
        motor.abs_turns[1]++;
            if( GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==1 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==1)
            {
                motor.turns[1]++;
            }
            else if(GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==0 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==1)
            {
                motor.turns[1]--;
            }//上升沿捕获
            else if( GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==0 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==0)
            {
                 motor.turns[1]++;
            }
            else if(GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==1 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==0)
            {
                 motor.turns[1]--;
            }//下降沿捕获
    }

    //9.2的捕获中断
    if (MAP_Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3))
    {
        MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3);
        BITBAND_PERI(TIMER_A_CMSIS(TIMER_A3_BASE)->CCTL[3], TIMER_A_CCTLN_COV_OFS) = 0;
     motor.abs_turns[1]++;
        if( GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==1 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==1)
        {
            motor.turns[1]--;
        }
        else if(GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==0 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==1)
        {
            motor.turns[1]++;
        }
        else if( GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==0 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==0)
        {
             motor.turns[1]--;
        }
        else if(GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)==1 && GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)==0)
        {
             motor.turns[1]++;
        }
    }

    //10.5的捕获中断
    if (MAP_Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1))
    {
        MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
        BITBAND_PERI(TIMER_A_CMSIS(TIMER_A3_BASE)->CCTL[1], TIMER_A_CCTLN_COV_OFS) = 0;
    motor.abs_turns[0]++;
        if( GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==1 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==1)
       {
            motor.turns[0]++;
       }
        else if(GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==0 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==1)
        {
            motor.turns[0]--;
        }
        else if(GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==1 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==0)
        {
            motor.turns[0]--;
        }
        else if(GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5)==0 &&  GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN4)==0)
        {
            motor.turns[0]++;
        }
    }
}


static void motor_pwm_init(uint16_t ccr0, uint16_t psc)//
{
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
//    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
    Timer_A_PWMConfig TimA0_PWMConfig;

    TimA0_PWMConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    TimA0_PWMConfig.clockSourceDivider = psc;
    TimA0_PWMConfig.timerPeriod = ccr0;
    TimA0_PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    TimA0_PWMConfig.compareOutputMode = TIMER_A_OUTPUTMODE_TOGGLE_SET;
    TimA0_PWMConfig.dutyCycle = 0;
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &TimA0_PWMConfig);

//    TimA0_PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
    TimA0_PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;//P2.5
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &TimA0_PWMConfig);
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
}
void motor_init(void)
{

    motor_pwm_init(1000, 12);
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN7);

//    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN7);

}


void motor_set_speed(int32_t set_speed[2])
{
    for( i = 0;i<2;i++)
    {
        if(set_speed[i] > 0)//反转in1->1.6 1.7 in2->3.6 3.7（TB6612）
        {
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6 + i*0x40);
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6 + i*0x40);
            MAP_Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3-i*0x02,ABS(set_speed[i]));
//            MAP_Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3+i*0x02,ABS(set_speed[i]));
        }
        else
        {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6 + i*0x40);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6 + i*0x40);
            MAP_Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3-i*0x02,ABS(set_speed[i]));
//            MAP_Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3+i*0x02,ABS(set_speed[i]));
        }
    }
}
void motor_stop(void){
    PID_init(&pwm_pid[0], PID_POSITION, pid[0], 1000,1000);
    PID_init(&pwm_pid[1], PID_POSITION, pid[1], 1000,1000);
 while(1)
 {
    wheel_pwm[0]=PID_calc(&pwm_pid[0], motor.speed[0],0);
    wheel_pwm[1]=PID_calc(&pwm_pid[1], motor.speed[1],0);
    motor_set_speed(wheel_pwm);
    delay_ms(10);
    if(motor.speed[0]==0 && motor.speed[0]==0)
    {
       delay_ms(10);
        if(motor.speed[0]==0 && motor.speed[0]==0)
            break;
    }


 }

}
void motor_stop_time(uint32_t time_ms)
{
    PID_init(&pwm_pid[0], PID_POSITION, pid[0], 1000,1000);
    PID_init(&pwm_pid[1], PID_POSITION, pid[1], 1000,1000);
    wheel_pwm[0]=PID_calc(&pwm_pid[0], motor.speed[0],0);
    wheel_pwm[1]=PID_calc(&pwm_pid[1], motor.speed[1],0);
    motor_set_speed(wheel_pwm);
    delay_ms(time_ms);
}

void motor_r_90(float s_r)
{
    cascade_PID_init(&motor.position_pid[0],opid[0],ipid[0],60,80,1000,1000);
    cascade_PID_init(&motor.position_pid[1],opid[1],ipid[1],60,80,1000,1000);
    motor.distance[0]=0;
    motor.distance[1]=0;
    while(1)
    {
        motor.pwm[0]=cascade_PID_calc(&motor.position_pid[0],motor.distance[0],motor.speed[0],-s_r);
        motor.pwm[1]=cascade_PID_calc(&motor.position_pid[1],motor.distance[1],motor.speed[1],s_r);
        motor_set_speed(motor.pwm);
        delay_ms(15);
        if(motor.speed[0]==0 || motor.speed[1]==0)
        {   motor_stop();
            cascade_PID_clear(&motor.position_pid[0]);
            cascade_PID_clear(&motor.position_pid[1]);
            motor.distance[0]=0;
            motor.distance[1]=0;
            break;
        }
    }
}

void motor_l_90(float s_l)
{   cascade_PID_init(&motor.position_pid[0],opid[0],ipid[0],60,60,1000,1000);
    cascade_PID_init(&motor.position_pid[1],opid[1],ipid[1],60,60,1000,1000);
    motor.distance[0]=0;
    motor.distance[1]=0;
    while(1)
    {
        motor.pwm[0]=cascade_PID_calc(&motor.position_pid[0],motor.distance[0],motor.speed[0],s_l);
        motor.pwm[1]=cascade_PID_calc(&motor.position_pid[1],motor.distance[1],motor.speed[1],-s_l);
        motor_set_speed(motor.pwm);
        delay_ms(15);
        if(motor.speed[0]==0 && motor.speed[1]==0)//&&或者||（考虑哪种好）
        {   motor_stop_time(100);
            cascade_PID_clear(&motor.position_pid[0]);
            cascade_PID_clear(&motor.position_pid[1]);
            motor.distance[0]=0;
            motor.distance[1]=0;
            break;
        }
    }
}

void motor_str(float s_str){
    cascade_PID_init(&motor.position_pid[0],opid[0],ipid[0],80,60,1000,1000);
    cascade_PID_init(&motor.position_pid[1],opid[1],ipid[1],130,60,1000,1000);
    motor.distance[0]=0;
    motor.distance[1]=0;
    while(1)
    {
        motor.pwm[0]=cascade_PID_calc(&motor.position_pid[0],motor.distance[0],motor.speed[0],s_str);
        motor.pwm[1]=cascade_PID_calc(&motor.position_pid[1],motor.distance[1],motor.speed[1],s_str);
        motor_set_speed(motor.pwm);
        transimit(motor.speed[0], motor.position_pid[0].v_set, motor.distance[0]);
        delay_ms(15);
        if(motor.speed[0]==0 && motor.speed[1]==0)
        {
            motor_stop();
            cascade_PID_clear(&motor.position_pid[0]);
            cascade_PID_clear(&motor.position_pid[1]);
            motor.distance[0]=0;
            motor.distance[1]=0;
            break;
        }
}
}

void motor_back(float s_back){
    cascade_PID_init(&motor.position_pid[0],opid[0],ipid[0],80,100,1000,1000);
    cascade_PID_init(&motor.position_pid[1],opid[1],ipid[1],80,100,1000,1000);
    motor.distance[0]=0;
    motor.distance[1]=0;
    while(1)
    {
        motor.pwm[0]=cascade_PID_calc(&motor.position_pid[0],motor.distance[0],motor.speed[0],-s_back);
        motor.pwm[1]=cascade_PID_calc(&motor.position_pid[1],motor.distance[1],motor.speed[1],-s_back);
        motor_set_speed(motor.pwm);
        delay_ms(15);
        if(motor.speed[0]==0 && motor.speed[1]==0)
        {
            motor_stop();
            cascade_PID_clear(&motor.position_pid[0]);
            cascade_PID_clear(&motor.position_pid[1]);
            motor.distance[0]=0;
            motor.distance[1]=0;
            break;
        }
}
}


void motor_mea(const motor_t*motor){
           if(motor->speed[0]>=0){
               OLED_ShowNum(32, 5, motor->speed[0],3, 8);
           }
           else{
               OLED_ShowString(26, 5,"-", 8);
               OLED_ShowNum(32, 5, ABS(motor->speed[0]), 3, 8);
           }
           if(motor->speed[1]>=0){
               OLED_ShowNum(1, 2, motor->speed[1], 3, 8);
                 }
           else{
               OLED_ShowString(0, 2, "-", 8);
              OLED_ShowNum(8, 2, ABS(motor->speed[1]), 3, 8);
           }

           OLED_ShowNum(56,3 ,  motor->distance[0], 3, 8);
           OLED_ShowNum(10, 3,  motor->distance[1], 3, 8);

}


void turn_R(float vr)//陀螺仪给角度
{
    PID_init(&pwm_pid[0], PID_POSITION, pid[0], 1000,1000);
    PID_init(&pwm_pid[1], PID_POSITION, pid[1], 1000,1000);
    wheel_pwm[0]=PID_calc(&pwm_pid[0], motor.speed[0],-vr);
    wheel_pwm[1]=PID_calc(&pwm_pid[1], motor.speed[1],vr);
    motor_set_speed(wheel_pwm);
    //delay_ms(10);
}
void turn_L(float vl)//陀螺仪给角度
{
    PID_init(&pwm_pid[0], PID_POSITION, pid[0], 1000,1000);
    PID_init(&pwm_pid[1], PID_POSITION, pid[1], 1000,1000);
    wheel_pwm[0]=PID_calc(&pwm_pid[0], motor.speed[0],vl);
    wheel_pwm[1]=PID_calc(&pwm_pid[1], motor.speed[1],-vl);
    motor_set_speed(wheel_pwm);
    //delay_ms(10);
}





