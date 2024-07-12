#ifndef __LED_H_
#define __LED_H_

#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_gpio.h"
#include "../task/task.h"
#include "stdint.h"

extern void led_set(uint8_t sta);

void led_blame(uint8_t start_time, uint8_t times, uint8_t sun_time,
               uint8_t moon_time);

#endif