#include "buzzer.h"
#include "../drive/gpio.h"

void buzzer_ring() { gpio_set_on(BUZZER); }
void buzzer_mute() { gpio_set_off(BUZZER); }

void buzzer_blame(uint8_t later_start, uint8_t times, uint8_t ring_time,
                  uint8_t mute_time) {
  gpio_set_blame(BUZZER, later_start, times, ring_time, mute_time);
}
