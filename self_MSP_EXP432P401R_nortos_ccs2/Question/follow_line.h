/*
 * follow_f.h
 *
 *  Created on: 2023年7月8日
 *      Author: bink
 */

#ifndef FOLLOW_F_H_
#define FOLLOW_F_H_
#define ABS(x) ((x)>=0?(x):-(x))
#define GO_SPEED 33
#include "external_devices\fmq.h"
#include "external_devices\motor.h"
#include "external_devices\RL.h"
#include "algorithm\pid.h"
#include "System\delay.h"

typedef struct
{
    float wd; //差速
    float set_speed[2];//预期速度
    float set_wd[2];
    int32_t wheel_pwm[2];//pid计算出的pwm值
    const motor_t *motor_info;//motor 的接口
    pid_type_def angle_pid[2];
    pid_type_def speed_pid[2];
    int count;
}follow_line_t;
const  follow_line_t* get_follow_line_info(void);
void set_follow_line_wd(void);
void follow_line_pid(void);
void follow_line_loop1(void);




#endif /* FOLLOW_F_H_ */
