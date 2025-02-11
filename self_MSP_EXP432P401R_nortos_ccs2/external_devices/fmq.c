/*
 * fmq.c
 *
 *  Created on: 2023年7月7日
 *      Author: bink
 */
/* Standard Includes */
/*description:蜂鸣器
 * 端口设置
 *  I/O->p5.0
 *  VCC->3.3V
 *  GND->GND
 *
 *
 */

#include "fmq.h"

void fmq_init(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN0);
}
void fmq_loop(void)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0);
}
void fmq_stop(void)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN0);
}
void fmq_loop_time(uint32_t time)
{
    fmq_loop();
    delay_s(time);
    fmq_stop();
}


