#include "LED.h"
#include "../task/task.h"
#include "stdint.h"
#include "ti_msp_dl_config.h"

void LED_set(uint8_t sta) {
  if (sta == 1) {
    DL_GPIO_setPins(LED_PORT_PORT, LED_PORT_LED_PIN);
  } else {
    DL_GPIO_clearPins(LED_PORT_PORT, LED_PORT_LED_PIN);
  }
}

void led_blame_sun(void *para);
void led_blame_moon(void *para);

void led_blame_moon(void *para) {
  LED_set(0);

  para--;
  if (((uint32_t)para & 0xff) == 0)
    return;

  uint32_t moon_time = ((uint32_t)para >> 16) & 0xff;

  Task t = task_new(led_blame_sun, para);
  task_timed_insert(&task.timed, t, moon_time);
}

void led_blame_sun(void *para) {
  LED_set(1);

  uint32_t sun_time = ((uint32_t)para >> 8) & 0xff;

  Task t = task_new(led_blame_moon, para);
  task_timed_insert(&task.timed, t, sun_time);
}

void led_blame(uint8_t start_time, uint8_t times, uint8_t sun_time,
               uint8_t moon_time) {
  if (times == 0)
    return;

  uint32_t para = moon_time << 16 | sun_time << 8 | times;

  Task t = task_new(led_blame_sun, (void *)para);
  task_timed_insert(&task.timed, t, start_time);
}
