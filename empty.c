#include "User/device/gw_gray.h"
#include "User/device/led.h"
#include "User/drive/delay.h"
#include "User/drive/interrupt/interrupt-timer.h"
#include "User/drive/interrupt/interrupt.h"
#include "User/move/turn.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "ti_msp_dl_config.h"
#include "User/device/flash.h"

uint32_t buf1[16] = {12, 4, 4563, 245, 2, 645, 13, 0xffffffff, 0x1fffff01};
uint32_t buf2[16] = {0};



int main(void) {
  SYSCFG_DL_init();

  status_init(&status);
  task_init(&task);

  interrupt_gpios_init();
  interrupt_uarts_init();
  interrupt_timers_init();

  led_blame(1, 500, 10, 10);

  erase_flash(0);

  ram2flash(0, buf1, 16);

  flash2ram(0, buf2, 16);

  //   status.base_speed = 500;
  //   status.mode.follow = true;

  while (1) {
    task_poll(&task);
  }
}
