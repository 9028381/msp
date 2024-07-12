#ifndef __LED_H__
#define __LED_H__

#include "stdint.h"

void led_on();
void led_off();

void led_blame(uint8_t later_start, uint8_t times, uint8_t sun_time,
               uint8_t moon_time);

#endif // !__LED_H__
