/*
 * follow_rect.c
 *
 *  Created on: 2023年8月3日
 *      Author: bink
 */
//#include "Tim32.h"
#include "calibration_angle.h"
#include "follow_rect.h"
target_angle target_angle_t;
void init_target_angle(){
    const calibration_init* calibration= get_calibration_info();
    target_angle_t.mode=0;
    target_angle_t.target_angle_x=calibration->calibration_angle[0][0];
    target_angle_t.target_angle_x=calibration->calibration_angle[0][1];
//    target_angl

}
void set_target_angle(){
    const calibration_init* calibration= get_calibration_info();

    while(1)
    {

    }
}
