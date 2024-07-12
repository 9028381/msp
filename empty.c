#include "User/device/buzzer.h"
#include "User/drive/delay.h"
#include "User/device/gw_gray.h"
#include "User/device/gyroscope.h"
#include "User/device/led.h"
#include "User/drive/motor.h"
#include "User/device/radar.h"
#include "User/device/servo.h"
#include "User/it/gpio_it.h"
#include "User/it/timer_it.h"
#include "User/it/uart_it.h"
#include "User/status/status.h"
#include "User/device/wheel.h"
#include "User/task/task.h"
#include "User/uart_re_driver.h"
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

int main(void) {
  SYSCFG_DL_init();

  status_init(&status);
  task_init(&task);

  enable_timer_it();
  enable_all_uart_it();
  enable_all_gpio_it();

    led_blame(100, 5, 10, 10);

    buzzer_buzz(50, 7, 20, 10);

    // start_follow_line(1);

    turn_abs_start_turn(90, 200);

  //print_start(20);

  while (1) {
    task_poll(&task);
  }
}
