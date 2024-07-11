#include "User/device/motor.h"
#include "User/device/gw_gray.h"
#include "User/device/gyroscope.h"
#include "User/device/servo.h"
#include "stdlib.h"
#include "string.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_dma.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "User/uart_re_driver.h"
#include "User/device/radar.h"
#include "User/status/status.h"
#include "User/status/wheel.h"
#include "User/utils/log.h"
#include <stdio.h>
#include "User/it/uart_it.h"
#include "User/it/gpio_it.h"
#include "User/it/timer_it.h"
#include "User/device/delay.h"

int main(void) {
  SYSCFG_DL_init();

    status_init(&status);

    enable_timer_it();
    enable_all_uart_it();
    enable_all_gpio_it();

  while (1) {

    delay_us(10);
    }
}


