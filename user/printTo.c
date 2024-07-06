#include "empty/ti_msp_dl_config.h"
#include "stdarg.h"
#include "stdio.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"

void printTo(enum print_device device, const char *format, ...) {
  static char str_buf[512] = {'\0'};

  va_list args;
  va_start(args, format);
  int len = vsnprintf(str_buf, 511, format, args);
  va_end(args);

      if (device == 1) {
    DL_DMA_setSrcAddr(DMA, DMA_CH1_CHAN_ID, (uint32_t)&str_buf[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH1_CHAN_ID, (uint32_t)(&UART_1_INST->TXDATA));
    DL_DMA_setTransferSize(DMA, DMA_CH1_CHAN_ID, len);

    // DL_DMA_enableChannel(DMA, DMA_CH1_CHAN_ID);
  }
  else if (device == 2) {
    DL_DMA_setSrcAddr(DMA, DMA_CH2_CHAN_ID, (uint32_t)&str_buf[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH2_CHAN_ID, (uint32_t)(&UART_2_INST->TXDATA));
    DL_DMA_setTransferSize(DMA, DMA_CH2_CHAN_ID, len);

    DL_DMA_enableChannel(DMA, DMA_CH2_CHAN_ID);
  }
  else if (device == 3) {
    DL_DMA_setSrcAddr(DMA, DMA_CH3_CHAN_ID, (uint32_t)&str_buf[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH3_CHAN_ID, (uint32_t)(&UART_3_INST->TXDATA));
    DL_DMA_setTransferSize(DMA, DMA_CH3_CHAN_ID, len);

    DL_DMA_enableChannel(DMA, DMA_CH3_CHAN_ID);
  }
  else if (device == 4) {
    DL_DMA_setSrcAddr(DMA, DMA_CH4_CHAN_ID, (uint32_t)&str_buf[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH4_CHAN_ID, (uint32_t)(&UART_4_INST->TXDATA));
    DL_DMA_setTransferSize(DMA, DMA_CH4_CHAN_ID, len);

    DL_DMA_enableChannel(DMA, DMA_CH4_CHAN_ID);
  }
  // delay_cycles(160000);
}
