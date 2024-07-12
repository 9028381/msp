#ifndef __BUZZER_H_
#define __BUZZER_H_

#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_gpio.h"
#include "../task/task.h"
#include "stdint.h"

void buzzer_set(uint8_t sta);
void buzzer_buzz(uint8_t start_time, uint8_t times, uint8_t on_time, uint8_t off_time);

#endif
