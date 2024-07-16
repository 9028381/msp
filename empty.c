#include "User/device/led.h"
#include "User/drive/interrupt/interrupt-timer.h"
#include "User/drive/interrupt/interrupt.h"
#include "User/move/turn.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "ti_msp_dl_config.h"
#include "User/device/flash.h"
#include "string.h"

uint32_t buf1[16] = {0xfff2ff11, 4, 4563, 245, 2, 645, 13, 0xffffffff, 0x1fffff01};
uint32_t buf2[16] = {0};



int main(void) {
  SYSCFG_DL_init();

  status_init(&status);
  task_init(&task);

  interrupt_gpios_init();
  interrupt_uarts_init();
  interrupt_timers_init();

  led_blame(1, 10, 10, 10);

  erase_flash(1);

  ram2flash(1, buf1, 16);

memcpy(buf2, (void *)0x00008000, 16*4);
//   flash2ram(1, buf2, 16);

  PRINTLN("%x", *(uint32_t *)(0x00008000));

  //   status.base_speed = 500;
  //   status.mode.follow = true;

  while (1) {
    task_poll(&task);
  }
}
