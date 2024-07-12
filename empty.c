#include "User/device/motor.h"
#include "User/device/gw_gray.h"
#include "User/device/gyroscope.h"
#include "User/device/servo.h"
#include "User/task/task.h"
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
#include "User/device/LED.h"
#include "User/task/task.h"

void led_blame_block(void * _ignore){
    LED_set(1);
    delay_us(500000);
    LED_set(0);
    delay_us(500000);
}

int main(void) {
  SYSCFG_DL_init();

    status_init(&status);
    task_init(&task);

    enable_timer_it();
    enable_all_uart_it();
    enable_all_gpio_it();
    //led_blame(20, 10, 10, 20);
    Task t = task_new(led_blame_block, NULL);
    task_queue_push(&task.queue, t);
        task_queue_push(&task.queue, t);
            task_queue_push(&task.queue, t);
    task_queue_push(&task.queue, t);
    task_queue_push(&task.queue, t);
    task_queue_push(&task.queue, t);


  while (1) {
    
    task_poll(&task);
    }
}


