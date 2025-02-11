/*
 * RL.c
 *
 *  Created on: 2023年7月7日
 *      Author: bink
 */
#include "RL.h"
#include"Communication\uart_to_pc.h"

uint8_t LineSensor_Read(uint32_t time)
{
    uint8_t result;

    //P5.3输出高电平,打开红外发射管
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
    //P7.0-7.7方向设置为输出
    GPIO_setAsOutputPin(GPIO_PORT_P7, PIN_ALL8);
    //设置P7.0-7.7输出高电平
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, PIN_ALL8);
    //延时10us
    delay_us(10);
    //P7.0-7.7方向设置为输入
    GPIO_setAsInputPin(GPIO_PORT_P7, PIN_ALL8);
    //延时特定时间
    delay_us(time);
    //读取P7.0-7.7的输入值
    result = P7->IN;

    //P5.3输出低电平,关闭红外发射管
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
    //返回端口读取值
    return result;
}
void DataPro(uint8_t SensorArray[], uint8_t* sum,uint8_t* left,uint8_t* right)
{
    *sum = 0;
    volatile uint8_t i;
    val = LineSensor_Read(DEBUG_TIME);
    if (val & 0x01)//被遮住了返回1，没被遮住返回0
    {
        SensorArray[0] = 1;//口1左1
    }
    else
    {
        SensorArray[0] = 0;
    }
    if (val & 0x02) {
         SensorArray[1] = 1;
    }
    else
    {
        SensorArray[1] = 0;
    }
    if (val & 0x04) {
        SensorArray[2] = 1;
    }
    else {
        SensorArray[2] = 0;
    }
    if (val & 0x08) {
        SensorArray[3] = 1;
    }
    else {
        SensorArray[3] = 0;
    }
    if (val & 0x10) {
        SensorArray[4] = 1;
    }
    else {
        SensorArray[4] = 0;
    }
    if (val & 0x20) {
        SensorArray[5] = 1;
    }
    else {
        SensorArray[5] = 0;
    }
    if (val & 0x40) {
        SensorArray[6] = 1;
    }
    else {
        SensorArray[6] = 0;
    }
//    if (val & 0x80) {
//        SensorArray[7] = 1;
//    }
//    else {
//        SensorArray[7] = 0;
//    }

    //计算感应到的传感器数量
//    findStatusOfSensor();
    for (i = 0; i < SENSOR_NUMBER-1; i++)
    {
        *sum += SensorArray[i];
    }
    for(i= 0;i< (SENSOR_NUMBER/2-1);i++)
    {
        *left += SensorArray[i];
    }
    for(i=SENSOR_NUMBER/2;i<(SENSOR_NUMBER-1);i++)
    {
        *right += SensorArray[i];
    }
}



