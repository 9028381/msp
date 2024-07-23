#include "User/device/key.h"
#include "User/device/led.h"
#include "User/device/servo.h"
#include "User/drive/interrupt/interrupt-timer.h"
#include "User/drive/interrupt/interrupt.h"
#include "User/move/turn.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "ti_msp_dl_config.h"

int main(void) {
  SYSCFG_DL_init();

  status_init(&status);
  task_init(&task);

  interrupt_gpios_init();
  interrupt_uarts_init();
  interrupt_timers_init();

  keyreact_init();

  led_blame(0, 5, 5, 5);

  status.base_speed = 400;
  status.mode.follow = true;

  /* status.mode.follow = true; */

  //   status.mode.turn = true;
  //   status.dir.target = 0;

  while (1) {
    task_poll(&task);
  }
}
