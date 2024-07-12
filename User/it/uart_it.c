/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-07 19:20:44
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-07 19:30:22
 * @FilePath: \empty\user\uart_it.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "uart_it.h"
#include "User/device/radar.h"
#include "User/device/ms_gray.h"

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
