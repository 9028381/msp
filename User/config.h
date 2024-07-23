#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "drive/uart.h"

#define DEV

#define MAX_TURN_SPEED 250
#define MAX_FOLLOW_TURN_SPEED 250

/******* TIMER *******/
#define TIMER1_FREQ 20

/******** FLASH *******/
#define BASE_ADDR 0x00008000
#define PAGE_SIZE 0x400
#define PAGE_NUM 16

/*
 * status
 */
#define STATUS_FREQ TIMER1_FREQ

/******* WHEEL *******/
#define WHEEL_THRUST_MAX 6000

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

/****** GW_GRAY ******/
#define GW_GRAY_CROSSROAD_MIN_RETURN_TIMES 8

#define ROAD_CROSS -30000
#define ROAD_TB 30000
#define ROAD_TL -25000
#define ROAD_TR 25000
#define ROAD_LEFT -20000
#define ROAD_RIGHT 20000

#endif // !__CONFIG_H__
