#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "device/uart.h"

#define DEV

#define PID_DATA_LOOP_LENGTH_MAX 40

#ifdef DEV
#define LOG_ENABLE
#endif // DEV

#define LOG_UART uart1
#define LOG_FORMAT_BUF_LENGTH 256

#endif // !__CONFIG_H__
