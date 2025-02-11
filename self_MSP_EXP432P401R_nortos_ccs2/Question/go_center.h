/*
 * go_center.h
 *
 *  Created on: 2023年8月3日
 *      Author: Emma
 */
#include "System\sysinit.h"
#include "algorithm/pid.h"
typedef struct {
    pid_type_def duoji_pid[2];
    int duoji_pwm[2];
    float dx;
    float dz;
    float dx1;
    float dz1;
}go_center_t;
const go_center_t* get_go_center_info(void);
void go_center_Init();
void go_center_loop();

