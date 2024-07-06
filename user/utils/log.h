#ifndef __LOG_H__
#define __LOG_H__

#include "../config.h"
#include "../device/uart.h"

void log_uprintf(enum Uart uart, const char *format, ...);

#define PRINTF(format, ...) log_uprintf(LOG_UART, format, ##__VA_ARGS__);
#define PRINTLN(format, ...) PRINTF(format "\r\n", ##__VA_ARGS__)
#define ERROR(format, ...) PRINTLN("E " format, ##__VA_ARGS__)
#define WARN(format, ...) PRINTLN("W " format, ##__VA_ARGS__)
#define INFO(format, ...) PRINTLN("I " format, ##__VA_ARGS__)
#define DEBUG(format, ...)                                                     \
  PRINTLN("D %s:%s:%u " format, __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define TRACE(var, fmt)                                                        \
  PRINTLN("T %s:%s:%u " #var "=" fmt, __FILE__, __func__, __LINE__, var)

#endif // !__LOG_H__
