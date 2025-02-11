/*
 * motor.h
 *
 *  Created on: 2023骞�7鏈�7鏃�
 *      Author: bink
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define ABS(x) ((x)>=0?(x):-(x))
#define CAP_REGISTER_SELECTION TIMER_A_CAPTURECOMPARE_REGISTER_1
#define CAP_CCR_NUM 1
#define CAP_PORT_PIN GPIO_PORT_P5, GPIO_PIN6
#define PI 3.1415926535
#define MOTOR_PSC   12
#define MOTOR_CCR0  100
#define MOTOR_PERIMETER  (6.8*PI)
#define MOTOR_RADIUS           3.4
#define CYCLE_TURNS 390
#define TA2_FREQ    100

#include"System\sysinit.h"
#include "algorithm\pid.h"
#include  "Communication/Communication.h"


typedef struct
{
    float speed[2];
    int32_t turns[2];
    int32_t pwm[2];
    float distance[2];
    uint32_t abs_turns[2];
    float abs_distance[2];
    cascade_pid_t position_pid[2];
    pid_type_def speed_pid[2];
}motor_t;
static void motor_pwm_init(uint16_t ccr0, uint16_t psc);
void TimA2_Int_Init(void);
void TA2_0_IRQHandler(void);
void TimA3_coder_init(void);
void TA3_0_IRQHandler(void);
void TA3_N_IRQHandler(void);
void motor_init(void);
void motor_set_speed(int32_t set_speed[2]);
void motor_stop(void);
void motor_stop_time(uint32_t time_ms);
//串行pid控制
void motor_r_90(float s_r);
void motor_l_90(float s_l);
void motor_str(float s_str);
void motor_back(float s_back);
void turn(void);
void motor_mea(const motor_t*motor);
void turn_R(float vr);
void turn_L(float vl);
const motor_t* get_motor_info(void);




#endif /* MOTOR_H_ */
