#include "../log.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void log_uprintf(enum Uart uart, const char *format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

int main(int argc, char *argv[]) {
  for (unsigned int times = 0; times <= 10000; times++)
    printf(LOG_TIME_FMT_TYPE "\n", LOG_TIME_FMT(times));

  status_init();
  for (unsigned int times = 0; times <= 10000; times++) {
    status_next();
    TRACE("trace", "%s");
  }

  return EXIT_SUCCESS;
}
