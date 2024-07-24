#include "key.h"
#include "User/config.h"
#include "User/status/record.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "led.h"
#include "ti_msp_dl_config.h"

void record_once_switch(void *para) {
  static bool is_first = true;

  if (is_first) {
    INFO("Start record");
    status.mode.record = true;
    status.rec.times = status.times;
    for (int i = 0; i < WHEEL_NUMS; i++)
      status.rec.wheels_history[i] = status.wheels[i].history;
    led_blame(0, 4, 5, 5);
    is_first = false;
  } else {
    INFO("Stop record");
    status.mode.record = false;
    status.rec.duration = status.times - status.rec.times;
    status_record_force_swap_mem();
    led_blame(0, 2, 10, 10);
  }
}

void repeat_stop(void *para) {
  INFO("Stop repeat");
  status.mode.repeat = false;
  led_blame(0, 5, 10, 10);
}

void repeat_open(void *para) {
  INFO("Start repeat");
  status.mode.repeat = true;
  status.rec.times = status.times;
  for (int i = 0; i < WHEEL_NUMS; i++)
    status.rec.wheels_history[i] = status.wheels[i].history;
  led_blame(0, 2, 10, 10);
  Task t = task_new(repeat_stop, NULL);
  task_timed_append(&task.timed, t, status.rec.duration - 1);
}

bool key1_is_press() { return !DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN); }
bool key2_is_press() { return !DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN); }

void task_timed_key_react_new(void (*key_react)(void *), void *para,
                              unsigned later) {
  Task t = task_new(key_react, para);
  task_timed_append(&task.timed, t, later);
}

void key1_react(void *callback) {
  if (key1_is_press()) {
    INFO("KEY_EVENT key1 press.");
    ((void (*)(void *))callback)(NULL);
    task_timed_key_react_new(key1_react, callback, STATUS_FREQ);
    return;
  }

  task_timed_key_react_new(key1_react, callback, 1);
}

void key2_react(void *callback) {
  if (key2_is_press()) {
    INFO("KEY_EVENT key1 press.");
    ((void (*)(void *))callback)(NULL);
    task_timed_key_react_new(key2_react, callback, STATUS_FREQ);
    return;
  }

  task_timed_key_react_new(key2_react, callback, 1);
}

void keyreact_init() {
  key1_react(record_once_switch);
  key2_react(repeat_open);
}
