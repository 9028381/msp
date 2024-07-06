#ifndef __LOG_H__
#define __LOG_H__

#include "../config.h"
#include "../device/uart.h"

void log_uprintf(enum Uart uart, const char *format, ...);

// #define PRINTF(...) uart_print(LOG_UART, __VA_ARGS__)
// #define PRINTF(format, ...) uart_print(LOG_UART, format, ##__VA_ARGS__);
// #define PRINTLN(format, ...) PRINTF(format "\r\n", __VA_ARGS__)
// #define ERROR(format, ...) PRINTLN("E " format, __VA_ARGS__)
// #define WARN(format, ...) PRINTLN("W " format, __VA_ARGS__)
// #define INFO(format, ...) printf("INFO " format "\r\n", ##__VA_ARGS__)
// #define INFO(format, ...) PRINTLN("I " format, __VA_ARGS__)
// #define DEBUG(format, ...) PRINTLN("D " format, __VA_ARGS__)
// #define TRACE(format, ...) PRINTLN("T " format, __VA_ARGS__)

#endif // !__LOG_H__
