/*
 * calibration_angle.h
 *
 *  Created on: 2023年8月3日
 *      Author: bink
 */

#ifndef QUESTION_CALIBRATION_ANGLE_H_
#define QUESTION_CALIBRATION_ANGLE_H_
#include "external_devices\getAngle.h"
#include "System\system.h"
typedef struct {
    int mode;
    float center_angle_x;
    double center_angle_z;
    double calibration_angle[4][2];//分别记录左上，右上，右下，左下，50cm正方形的四角坐标时的角度
}calibration_init;
const calibration_init* get_calibration_info(void);
void calibration_angle_init();
void PORT1_IRQHandler(void);
#endif /* QUESTION_CALIBRATION_ANGLE_H_ */
