#include "log.h"
#include "stdarg.h"
#include "stdio.h"

void log_uprintf(enum Uart uart, const char *format, ...) {
  static unsigned char abbuf = 0;
  static char buf[2][LOG_FORMAT_BUF_LENGTH];

  abbuf = abbuf ? 0 : 1;

  va_list args;
  va_start(args, format);
  unsigned int len =
      vsnprintf(buf[abbuf], LOG_FORMAT_BUF_LENGTH - 1, format, args);
  va_end(args);

  uart_send(uart, buf, len);
}
