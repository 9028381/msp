#include "uart.h"
#include "empty/ti_msp_dl_config.h"
#include "ti/driverlib/dl_dma.h"

#define UART_DMA_SEND(channel, data, len, dest)                                \
  while (DL_DMA_isChannelEnabled(DMA, channel))                                \
    continue;                                                                  \
  DL_DMA_setSrcAddr(DMA, channel, (uint32_t)data);                             \
  DL_DMA_setDestAddr(DMA, channel, (uint32_t)dest);                            \
  DL_DMA_setTransferSize(DMA, channel, len);                                   \
  DL_DMA_enableChannel(DMA, channel);

void uart_dma_send(enum Uart uart, const void *src, unsigned int len) {
  switch (uart) {
  case uart1:
    UART_DMA_SEND(DMA_CH1_CHAN_ID, src, len, &UART_1_INST->TXDATA);
    break;
  case uart2:
    UART_DMA_SEND(DMA_CH2_CHAN_ID, src, len, &UART_2_INST->TXDATA);
    break;
  case uart3:
    UART_DMA_SEND(DMA_CH3_CHAN_ID, src, len, &UART_3_INST->TXDATA);
    break;
  case uart4:
    UART_DMA_SEND(DMA_CH4_CHAN_ID, src, len, &UART_4_INST->TXDATA);
    break;
  default:
    break;
  }
}
