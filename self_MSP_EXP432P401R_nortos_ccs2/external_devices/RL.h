/*
 * RL.h
 *
 *  Created on: 2023年7月7日
 *      Author: bink
 */
#include "System\sysinit.h"
#include "Red_line.h"
#ifndef RL_H_
#define RL_H_
#define DEBUG_TIME 1000 //用于调试传感器
#define SENSOR_NUMBER 8 //用于定义传感器数量
uint8_t val;
uint8_t SensorArray[SENSOR_NUMBER];
uint8_t sum;
uint8_t left;
uint8_t right;
uint8_t LineSensor_Read(uint32_t time);
void DataPro(uint8_t SensorArray[], uint8_t* sum,uint8_t* left,uint8_t* right);
#endif /* RL_H_ */
