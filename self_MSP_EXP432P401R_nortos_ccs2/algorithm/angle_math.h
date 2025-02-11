/*
 * angle_math.h
 *
 *  Created on: 2023年8月3日
 *      Author: bink
 */

#ifndef ALGORITHM_ANGLE_MATH_H_
#define ALGORITHM_ANGLE_MATH_H_
                              //想要打到    目标点的坐标

#define  actual_center_x  0//中心值的坐标,已原点为（0，0） 四个角分别为（-0.25，0.25） （-0.25，-0。25）（0.25，-0.25）（0.25,0.25）
#define  actual_control_1 -0.25//25厘米处的矫正坐标    四个角分别为（-0.25，0.25） （-0.25，-0。25）（0.25，-0.25）（0.25,0.25）
#define  actual_control_2  0.25
#define  calibration_angle_0 14.03624347
#include"System\System.h"
//double calculate_actual_angle(double actual_x );



#endif /* ALGORITHM_ANGLE_MATH_H_ */
