#include "User/status/status.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"

void TIMER_INT_INST_IRQHandler() {
  switch (DL_TimerG_getPendingInterrupt(TIMER_INT_INST)) {
  case DL_TIMER_IIDX_ZERO:
    status_next(&status);

    break;
  default:
    break;
  }
}

void interrupt_timers_init() {
  NVIC_EnableIRQ(TIMER_INT_INST_INT_IRQN);
  DL_TimerG_startCounter(TIMER_INT_INST);
}
