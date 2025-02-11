/*
 * findway.c
 *
 *  Created on: 2023Äê7ÔÂ15ÈÕ
 *      Author: 32753
 */

#ifndef FINDWAY_C_
#define FINDWAY_C_
#include <external_devices/Red_line.h>
uint32_t RL_booldata[8];
void findStatusOfSensor()
{
    GPIO_setAsInputPin(GPIO_PORT_P8, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P8, GPIO_PIN7);
    GPIO_setAsInputPin(GPIO_PORT_P9, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P8, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P9, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN2);
    RL_booldata[0]=GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN6);
    RL_booldata[1]=GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN7);
    RL_booldata[2]=GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN1);
    RL_booldata[3]=GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN3);
    RL_booldata[4]=GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN3);
    RL_booldata[5]=GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN3);
    RL_booldata[6]=GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN3);
    RL_booldata[7]=GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN2);
}



#endif /* FINDWAY_C_ */
