/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-06 11:47:01
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-06 17:44:53
 * @FilePath: \empty\user\utils\test\log.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "../log.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

struct Status status;

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
