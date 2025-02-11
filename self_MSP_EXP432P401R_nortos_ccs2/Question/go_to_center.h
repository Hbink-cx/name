/*
 * go_to_center.h
 *
 *  Created on: 2023年8月4日
 *      Author: bink
 */

#ifndef QUESTION_GO_TO_CENTER_H_
#define QUESTION_GO_TO_CENTER_H_
#include "System\System.h"
#include "algorithm\pid.h"
typedef struct
{
    pid_type_def duoji_pid[2];
    int duoji_pwm[2];
    int center_x;
    int center_y;
    int target_x;
    int target_y;
}coordinate;
void go_to_center();
void go_to_center_init();
void go_to_center_loop();

#endif /* QUESTION_GO_TO_CENTER_H_ */
