#ifndef __LOG_H__
#define __LOG_H__

#include "../config.h"
#include "../device/uart.h"

void log_uprintf(enum Uart uart, const char *format, ...);

// #define FMT_TYPE(X)                                                            \
//   _Generic((X),                                                                \
//       int: "%d",                                                               \
//       float: "%f",                                                             \
//       double: "%f",                                                            \
//       char: "%c",                                                              \
//       char *: "%s",                                                            \
//       default: "%p")

#define PRINTF(fmt, ...) log_uprintf(LOG_UART, fmt, ##__VA_ARGS__);
#define PRINTLN(fmt, ...) PRINTF(fmt "\r\n", ##__VA_ARGS__)
#define ERROR(fmt, ...) PRINTLN("E " fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) PRINTLN("W " fmt, ##__VA_ARGS__)
#define INFO(fmt, ...) PRINTLN("I " fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...)                                                        \
  PRINTLN("D %s:%s:%u " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define TRACE(var, fmt)                                                        \
  PRINTLN("T %s:%s:%u " #var "=" fmt, __FILE__, __func__, __LINE__, var)

#ifndef LOG_ENABLE
#undef ERROR
#undef WARN
#undef INFO
#undef DEBUG
#undef TRACE
#define ERROR(format, ...)
#define WARN(format, ...)
#define INFO(format, ...)
#define DEBUG(format, ...)
#define TRACE(var, fmt)
#endif // !LOG_ENABLE

#endif // !__LOG_H__
