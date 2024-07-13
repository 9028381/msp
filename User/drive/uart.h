#ifndef __UART_H__
#define __UART_H__

enum Uart {
  uart1 = 0,
  uart2 = 1,
  uart3 = 2,
  uart4 = 3,
};

void uart_dma_send(enum Uart uart, const void *src, unsigned int len);

#endif // !__UART_H__
