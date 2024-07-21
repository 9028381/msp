#include "User/device/wheel.h"
#include "User/status/status.h"
#include "User/utils/log.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"
#include "User/device/cam.h"
#include "User/status/status.h"

void TIMER_INT_INST_IRQHandler() {
  switch (DL_TimerG_getPendingInterrupt(TIMER_INT_INST)) {
  case DL_TIMER_IIDX_ZERO:
    DL_WWDT_restart(WWDT0_INST);
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
