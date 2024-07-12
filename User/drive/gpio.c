#include "gpio.h"
#include "../task/task.h"
#include "ti_msp_dl_config.h"

void gpio_set_on(enum Gpio io) {
  switch (io) {
  case LED:
    DL_GPIO_setPins(LED_PORT_PORT, LED_PORT_LED_PIN);
    break;
  case BUZZER:
    DL_GPIO_clearPins(BUZZER_PORT_PORT, BUZZER_PORT_BUZZER_PIN_PIN);
    break;
  default:
    break;
  }
}

void gpio_set_off(enum Gpio io) {
  switch (io) {
  case LED:
    DL_GPIO_clearPins(LED_PORT_PORT, LED_PORT_LED_PIN);
    break;
  case BUZZER:
    DL_GPIO_setPins(BUZZER_PORT_PORT, BUZZER_PORT_BUZZER_PIN_PIN);
    break;
  default:
    break;
  }
}

void gpio_blame_on(void *para);
void gpio_blame_off(void *para);

// data  io | off_time | on_time | times
void gpio_set_blame(enum Gpio io, uint8_t later_start, uint8_t times,
                    uint8_t on_time, uint8_t off_time) {
  if (times == 0)
    return;

  uint32_t para = (io & 0xff) << 24 | off_time << 16 | on_time << 8 | times;

  Task t = task_new(gpio_blame_on, (void *)para);
  task_timed_append(&task.timed, t, later_start);
}

void gpio_blame_on(void *para) {
  uint32_t data = (uint32_t)para;

  uint8_t on_time = (data >> 8) & 0xff;
  enum Gpio io = (data >> 24) & 0xff;

  gpio_set_on(io);

  Task t = task_new(gpio_blame_off, para);
  task_timed_append(&task.timed, t, on_time);
}

void gpio_blame_off(void *para) {
  uint32_t data = (uint32_t)para;

  uint8_t off_time = (data >> 16) & 0xff;
  enum Gpio io = (data >> 24) & 0xff;

  gpio_set_off(io);

  data -= 1;
  if ((data & 0xff) == 0)
    return;

  Task t = task_new(gpio_blame_on, (void *)data);
  task_timed_append(&task.timed, t, off_time);
}
