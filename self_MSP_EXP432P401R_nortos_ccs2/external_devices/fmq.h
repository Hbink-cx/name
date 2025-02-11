/*
 * fmq.h
 *
 *  Created on: 2023Äê7ÔÂ7ÈÕ
 *      Author: bink
 */

#ifndef FMQ_H_
#define FMQ_H_
#include "System\sysinit.h"
void fmq_init(void);
void fmq_loop(void);
void fmq_stop(void);
void fmq_loop_time(uint32_t time);
#endif /* FMQ_H_ */
