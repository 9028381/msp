#ifndef __LOG_H__
#define __LOG_H__

#include "../config.h"
#include "../drive/uart.h"
#include "../status/status.h"

void log_uprintf(enum Uart uart, const char *format, ...);

#define PRINTF(fmt, ...) log_uprintf(LOG_UART, fmt, ##__VA_ARGS__);
#define PRINTLN(fmt, ...) PRINTF(fmt "\r\n", ##__VA_ARGS__)

/// minute:second:frame
#define LOG_TIME_FMT_TYPE "%02u:%02u:%02u"
/// t -> status.time
/// status.time -> ((minute * 60) + second) * STATUS_FREQ + frame
#define LOG_TIME_FMT(t)                                                        \
  ((t / STATUS_FREQ) / 60), ((t / STATUS_FREQ) % 60), (t % STATUS_FREQ)

/// >>> level time str
/// >>> L 00:00:00 str
#define LOG_EVENT(level, fmt, ...)                                             \
  PRINTLN(level " " LOG_TIME_FMT_TYPE " " fmt, LOG_TIME_FMT(status.times),     \
          ##__VA_ARGS__)

/// >>> level time span str
/// >>> L 00:00:00 func:line str
#define LOG_SPAN(level, fmt, ...)                                              \
  LOG_EVENT(level, "%s:%u " fmt, __func__, __LINE__, ##__VA_ARGS__)

/// >>> E 00:00:00 str
#define ERROR(fmt, ...) LOG_EVENT("E", fmt, ##__VA_ARGS__)
/// >>> W 00:00:00 str
#define WARN(fmt, ...) LOG_EVENT("W", fmt, ##__VA_ARGS__)
/// >>> I 00:00:00 str
#define INFO(fmt, ...) LOG_EVENT("I", fmt, ##__VA_ARGS__)
/// >>> D 00:00:00 func:8 str
#define DEBUG(fmt, ...) LOG_SPAN("D", fmt, ##__VA_ARGS__)
/// >>> T 00:00:00 func:8 var=8
#define TRACE(var, fmt) LOG_SPAN("T", #var "=" fmt, var)

/// >>> E 00:00:00 func:8 ERROR_TYPE str
#define THROW_ERROR(fmt, ...) LOG_SPAN("E", fmt, ##__VA_ARGS__)
/// >>> W 00:00:00 func:8 ERROR_TYPE str
#define THROW_WARN(fmt, ...) LOG_SPAN("W", fmt, ##__VA_ARGS__)

#ifdef DEV
#define LOG_ENABLE
#endif // DEV

#ifndef LOG_ENABLE
/// ignore log print
#undef LOG_EVENT
#define LOG_EVENT(level, fmt, ...)
#endif // !LOG_ENABLE

#endif // !__LOG_H__
