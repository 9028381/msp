#include "../uart.h"
#include "User/task/rpc.h"
#include "User/task/task.h"
#include "User/uart_re_driver.h"
#include "interrupt-timer.h"
#include "stdint.h"
#include "ti_msp_dl_config.h"

void interrupt_timers_init(void) {
  NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
  NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
  NVIC_ClearPendingIRQ(UART_3_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_3_INST_INT_IRQN); // 使能 接收中断
  NVIC_ClearPendingIRQ(UART_4_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_4_INST_INT_IRQN); // 使能 接收中断
}

void uart_rpc_drive(enum Uart which, uint8_t rev);

void UART_1_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_1_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    uint8_t buf = DL_UART_Main_receiveData(UART_1_INST);
    uart_rpc_drive(uart1, buf);

    break;
  default:
    break;
  }
}

void UART_2_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_2_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    uint8_t buf = DL_UART_Main_receiveData(UART_2_INST);
    // update_ms_diff(buf);

    break;
  default:
    break;
  }
}

void UART_3_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_3_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    uint8_t buf = DL_UART_Main_receiveData(UART_3_INST);
    uart_rpc_drive(uart3, buf);

    break;
  default:
    break;
  }
}

void UART_4_INST_IRQHandler(void) {
  switch (DL_UART_Main_getPendingInterrupt(UART_4_INST)) {
  case DL_UART_MAIN_IIDX_RX:

    uint8_t buf = DL_UART_Main_receiveData(UART_4_INST);
    uart_rpc_drive(uart4, buf);

    break;
  default:
    break;
  }
}

void uart_rpc_task_queue_call(void *para) {
  uint32_t data = (uint32_t)para;
  uint8_t id = (data >> 16) & 0xff;
  uint16_t var = data & 0xffff;
  task_rpc_call_id(task.rpc, id, var);
}

void uart_rpc_drive(enum Uart which, uint8_t rev) {
  static uint32_t data[4] = {0};

  data[which] = data[which] << 8 | rev;

  if ((data[which] >> 24) == 0xff) {
    Task t = task_new(uart_rpc_task_queue_call, (void *)data[which]);
    task_queue_push(&task.queue, t);
    data[which] = 0;
  }
}
