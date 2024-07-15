#include "User/device/led.h"
#include "User/drive/interrupt/interrupt-timer.h"
#include "User/drive/interrupt/interrupt.h"
#include "User/move/turn.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "ti_msp_dl_config.h"
#include "User/drive/delay.h"
#include "User/device/gw_gray.h"
#include "User/utils/log.h"

int main(void) {
  SYSCFG_DL_init();

  status_init(&status);
  task_init(&task);

  interrupt_gpios_init();
  interrupt_uarts_init();
  interrupt_timers_init();

  led_blame(1, 5, 10, 10);
 
//   status.base_speed = 500;
//   status.mode.follow = true;

  while (1) {
    task_poll(&task);
  }
}
