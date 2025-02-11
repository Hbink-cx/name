/*
 * angle_math.c
 *
 *  Created on: 2023年8月3日
 *      Author: bink
 */
#include "math.h"
#include "angle_math.h"
#include "Question\calibration_angle.h"
//double actual_x =-0.1  ;    //想要打到    目标点的坐标
//double actual_center_x=0;//中心值的坐标,已原点为（0，0） 四个角分别为（-0.25，0.25） （-0.25，-0。25）（0.25，-0.25）（0.25,0.25）
//double actual_cm_5_control_x=-0.25;//25厘米处的矫正坐标    四个角分别为（-0.25，0.25） （-0.25，-0。25）（0.25，-0.25）（0.25,0.25）
////    int cm_5_control_x-center // 五厘米处偏移像素
//// double sb=atan(actual_x-actual_center_x);
//// double actual_angle;     //实际的目标角度
//double actual_center_angle =90.0 ;//实际的中心点的角度
//double actual_cm_5_control_angle =104.4;//矫正值的角度
int angle_math_mode=0;
//
double calculate_actual_angle(double actual_x)
{
    const calibration_init * calibration_init_t =  get_calibration_info();
//    double actual_angle_z;
    volatile  double actual_control_angle = calibration_angle_0 +calibration_init_t->center_angle_x;
     double actual_angle_x=(calibration_init_t->calibration_angle[0][0]-calibration_init_t->center_angle_x)*(atan(actual_x-actual_center_x))/(atan(actual_control_1-actual_center_x))+calibration_init_t->center_angle_x;
    return actual_angle_x;
}
