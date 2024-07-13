#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "drive/uart.h"

#define DEV

#define MAX_TURN_SPEED 700
#define MAX_FOLLOW_TURN_SPEED 700

/******* TIMER *******/
#define TIMER1_FREQ 20

/*
 * status
 */
#define STATUS_FREQ TIMER1_FREQ

/******* WHEEL *******/
#define WHEEL_THRUST_MAX 9999

/*
 * task
 */
#define TASK_RPC_ID_LIMIT 30
#define TASK_QUEUE_LIMIT 30
#define TASK_TIMED_LIMIT 30

/*
 * utils
 */

/******** PID ********/
#define PID_DATA_LOOP_LENGTH_MAX 40

/******** LOG ********/
#define LOG_UART uart1
#define LOG_FORMAT_BUF_LENGTH 256

#endif // !__CONFIG_H__
