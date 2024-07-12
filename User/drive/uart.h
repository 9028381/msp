#ifndef __UART_H__
#define __UART_H__

enum Uart {
  uart1,
  uart2,
  uart3,
  uart4,
};

void uart_dma_send(enum Uart uart, const void *src, unsigned int len);

#endif // !__UART_H__
