#include "uart_it.h"
#include "../drive/uart.h"
#include "User/uart_re_driver.h"
#include "stdint.h"
#include "ti_msp_dl_config.h"

uint8_t r1_buf = 0;
uint8_t r2_buf = 0;
uint8_t r3_buf = 0;
uint8_t r4_buf = 0;

void enable_all_uart_it(void) {
  NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
  NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
  NVIC_ClearPendingIRQ(UART_3_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_3_INST_INT_IRQN); // 使能 接收中断
  NVIC_ClearPendingIRQ(UART_4_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_4_INST_INT_IRQN); // 使能 接收中断
}

void UART_1_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_1_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    r1_buf = DL_UART_Main_receiveData(UART_1_INST);

    break;
  default:
    break;
  }
}

void UART_2_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_2_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    r2_buf = DL_UART_Main_receiveData(UART_2_INST);
    update_ms_diff(r2_buf);

    break;
  default:
    break;
  }
}

void UART_3_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_3_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    r3_buf = DL_UART_Main_receiveData(UART_3_INST);
    uart_re_driver(uart3, r3_buf);

    break;
  default:
    break;
  }
}

void UART_4_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_4_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    r4_buf = DL_UART_Main_receiveData(UART_4_INST);
    uart_re_driver(uart4, r4_buf);

    break;
  default:
    break;
  }
}
