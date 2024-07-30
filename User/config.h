#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "drive/uart.h"

#define DEV

#define BASE_SPEED 500
#define KEEP_ANGLE_SPEED 700
#define TURN_ANGLE_SPEED 700
#define FOLLOW_LINE_SPEED 650

#define TURN_ANGLE_RANGE 1.0

#define MAX_TURN_SPEED 300
#define MAX_FOLLOW_TURN_SPEED 250

/******* TIMER *******/
#define TIMER1_FREQ 40

/******** FLASH *******/
#define BASE_ADDR 0x0010000
#define PAGE_SIZE 0x400
#define PAGE_NUM 64

/*
 * status
 */
#define STATUS_FREQ TIMER1_FREQ

#define STATUS_STEP_LIMIT 50

/******* WHEEL *******/
#define WHEEL_THRUST_MAX 5500

/*
 * task
 */
#define TASK_RPC_ID_LIMIT 160
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
#define GW_GRAY_ROAD_MIN_RETURN_TIMES 15

#define ROAD_NO 30001
#define ROAD_CROSS -30000
#define ROAD_TB 30000
#define ROAD_TL -25000
#define ROAD_TR 25000
#define ROAD_LEFT -20000
#define ROAD_RIGHT 20000

#endif // !__CONFIG_H__
