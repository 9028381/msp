#ifndef __PRINT_TO_H_
#define __PRINT_TO_H_

extern void printTo(int uart, const char *format, ...);

enum print_device {
  uart1 = 1,
  uart2 = 2,
  uart3 = 3,
  uart4 = 4,
};

#endif
