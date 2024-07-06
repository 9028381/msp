#include "../log.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void log_uprintf(enum Uart uart, const char *format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

int main(int argc, char *argv[]) {
  log_uprintf(uart1, "log uprintf!\n");
  PRINTF("printf %d\n", 123);
  PRINTLN("println");
  ERROR("error %s", "abc");
  WARN("warn %c", 'A');
  INFO("info %g", 3.14);
  DEBUG("debug");

  int var = 10;
  TRACE(var, "%d");
  return EXIT_SUCCESS;
}
