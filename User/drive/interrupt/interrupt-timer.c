#include "User/device/wheel.h"
#include "User/status/status.h"
#include "User/utils/log.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"
#include "User/device/cam.h"
#include "User/device/radar.h"
#include "User/device/ccd.h"


uint8_t buf[8] = {0};
uint8_t cnt = 0;

void TIMER_INT_INST_IRQHandler() {
  switch (DL_TimerG_getPendingInterrupt(TIMER_INT_INST)) {
  case DL_TIMER_IIDX_ZERO:
    status_next(&status);
    get_ccd_val();
    
    break;
  default:
    break;
  }
}

void interrupt_timers_init() {
  NVIC_EnableIRQ(TIMER_INT_INST_INT_IRQN);
  DL_TimerG_startCounter(TIMER_INT_INST);
}
