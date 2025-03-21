#include "User/device/key.h"
#include "User/device/led.h"
#include "User/device/servo.h"
#include "User/drive/interrupt/interrupt-timer.h"
#include "User/drive/interrupt/interrupt.h"
#include "User/move/turn.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "ti_msp_dl_config.h"
#include "User/device/radar.h"
#include "User/utils/utils.h"
#include "ti/driverlib/dl_uart.h"

int main(void) {
  SYSCFG_DL_init();

  status_init(&status);
  task_init(&task);

  interrupt_gpios_init();
  interrupt_uarts_init();
  interrupt_timers_init();

//   status.mode.remote = true;

  keyreact_init();
  led_blame(0, 5, 5, 5);


    // status.mode.remote = true;
//   status.mode.turn = true;
//   status.dir.target = 0;

  while (1) {
    task_poll(&task);
  }
}
