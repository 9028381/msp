#include "led.h"
#include "../drive/gpio.h"

void led_on() { gpio_set_on(LED); }
void led_off() { gpio_set_off(LED); }

void led_blame(uint8_t later_start, uint8_t times, uint8_t sun_time,
               uint8_t moon_time) {
  gpio_set_blame(LED, later_start, times, sun_time, moon_time);
}
