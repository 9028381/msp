#ifndef __GPIO_H__
#define __GPIO_H__

#include "stdint.h"

enum Gpio {
  LED = 0,
  BUZZER = 1,
};

void gpio_set_on(enum Gpio io);
void gpio_set_off(enum Gpio io);

void gpio_set_blame(enum Gpio io, uint8_t later_start, uint8_t times,
                    uint8_t on_time, uint8_t off_time);

#endif // !__GPIO_H__
