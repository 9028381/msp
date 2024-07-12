#include "timer_it.h"
#include "ti/driverlib/dl_timerg.h"

void TIMER_INT_INST_IRQHandler(void) {
  switch (DL_TimerG_getPendingInterrupt(TIMER_INT_INST)) {
  case DL_TIMER_IIDX_ZERO:
    status_next(&status);
    status_drive(&status);

    break;
  default:
    break;
  }
}

void enable_timer_it(void)
{
    NVIC_EnableIRQ(TIMER_INT_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_INT_INST);
}