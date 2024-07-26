#include "User/device/wheel.h"
#include "User/status/status.h"
#include "User/utils/log.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"
#include "User/device/cam.h"
#include "User/device/radar.h"


uint8_t buf[8] = {0};
uint8_t cnt = 0;

void TIMER_INT_INST_IRQHandler() {
  switch (DL_TimerG_getPendingInterrupt(TIMER_INT_INST)) {
  case DL_TIMER_IIDX_ZERO:
    DL_WWDT_restart(WWDT0_INST);
    status_next(&status);  
    PRINTLN("%d", radar_data[0]);

        
    break;
  default:
    break;
  }
}

void RE_TIMER_INST_IRQHandler() {
  switch (DL_TimerG_getPendingInterrupt(RE_TIMER_INST)) {
  case DL_TIMER_IIDX_ZERO:
    cnt = DL_UART_drainRXFIFO(UART2, &buf, 8);
    if(cnt)
        for(int i = 0; i < cnt; i++)
    {
            Ladar_drive(buf[i]);  
    }

        
    break;
  default:
    break;
  }
}

void interrupt_timers_init() {
  NVIC_EnableIRQ(TIMER_INT_INST_INT_IRQN);
  DL_TimerG_startCounter(TIMER_INT_INST);
  NVIC_EnableIRQ(RE_TIMER_INST_INT_IRQN);
  DL_TimerG_startCounter(RE_TIMER_INST);
}
