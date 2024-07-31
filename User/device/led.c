#include "led.h"
#include "../config.h"
#include "../drive/gpio.h"

void led_on() { gpio_set_on(LED); }
void led_off() { gpio_set_off(LED); }

void led_blame(uint8_t later_start, uint8_t times, uint8_t sun_time,
               uint8_t moon_time) {
  gpio_set_blame(LED, later_start, times, sun_time, moon_time);
}

void led_indicate_key_press() {
  led_blame(0, 3, STATUS_FREQ / 5, STATUS_FREQ / 5);
}

void led_indicate_step_complete() {
  led_blame(0, 3, STATUS_FREQ * 3 / 10, STATUS_FREQ * 3 / 10);
}
