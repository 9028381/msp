#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "device/uart.h"

#define DEV

/******* STATUS ******/
#define STATUS_FREQ 20

/******* WHEEL *******/
#define WHEEL_THRUST_MAX 9999

/******** PID ********/
#define PID_DATA_LOOP_LENGTH_MAX 40

/******** LOG ********/
#ifdef DEV
#define LOG_ENABLE
#endif // DEV

#define LOG_UART uart1
#define LOG_FORMAT_BUF_LENGTH 256

#endif // !__CONFIG_H__
