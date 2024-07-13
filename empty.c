#include "User/device/buzzer.h"
#include "User/drive/delay.h"
#include "User/device/gw_gray.h"
#include "User/device/gyroscope.h"
#include "User/device/led.h"
#include "User/drive/interrupt/interrupt-timer.h"
#include "User/drive/motor.h"
#include "User/device/radar.h"
#include "User/device/servo.h"
#include "User/status/status.h"
#include "User/device/wheel.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "stdlib.h"
#include "string.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_dma.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include <stdio.h>
#include "User/move/follow_line.h"
#include "User/move/turn.h"
#include "User/drive/interrupt/interrupt.h"

int main(void) {
  SYSCFG_DL_init();

  status_init(&status);
  task_init(&task);

  interrupt_timers_init();
  interrupt_uarts_init();
  interrupt_gpios_init();

    led_blame(100, 5, 10, 10);

    turn_abs_head_init();

    turn_abs_start_turn(90, 0);

  //print_start(20);

  while (1) {
    task_poll(&task);
  }
}
