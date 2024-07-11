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

union LedPara {
  void *point;
  uint8_t array[3];
};

void led_blame_moon(void *para) {
  union LedPara blame = (union LedPara)para;
  LED_set(0);

  blame.array[0]--;
  if (blame.array[0] == 0)
    return;

  Task t = task_new(led_blame_sun, blame.point);
  task_timed_insert(&task.timed, t, blame.array[2]);
}

void led_blame_sun(void *para) {
  union LedPara blame = (union LedPara)para;
  LED_set(1);

  Task t = task_new(led_blame_moon, blame.point);
  task_timed_insert(&task.timed, t, blame.array[1]);
}

void led_blame(uint8_t start_time, uint8_t times, uint8_t sun_time,
               uint8_t moon_time) {
  union LedPara para;
  para.array[0] = times;
  para.array[1] = sun_time;
  para.array[2] = moon_time;

  Task t = task_new(led_blame_sun, para.point);
  task_timed_insert(&task.timed, t, start_time);
}
