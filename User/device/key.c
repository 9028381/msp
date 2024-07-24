#include "key.h"
#include "User/config.h"
#include "User/status/record.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "led.h"
#include "ti_msp_dl_config.h"

void key1_callback() {
  static bool is_first = true;

  if (is_first) {
    status.mode.record = true;
    status.mode.repeat = false;
    status.rec_start.times = status.times;
    for (int i = 0; i < WHEEL_NUMS; i++)
      status.rec_start.wheels_history[i] = status.wheels[i].history;
    led_blame(0, 2, 5, 5);
    INFO("Start record");
    is_first = false;
  } else {
    status.mode.record = false;
    status_record_force_swap_mem();
    led_blame(0, 3, 10, 10);
    INFO("Stop record");
  }
}

void key2_callback() {
  INFO("Start repeat");
  status.mode.record = false;
  status.mode.repeat = true;
  status.rec_start.times = status.times;
  for (int i = 0; i < WHEEL_NUMS; i++)
    status.rec_start.wheels_history[i] = status.wheels[i].history;
  led_blame(0, 2, 5, 5);
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
    ((void (*)())callback)();
    task_timed_key_react_new(key1_react, callback, STATUS_FREQ);
    return;
  }

  task_timed_key_react_new(key1_react, callback, 1);
}

void key2_react(void *callback) {
  if (key2_is_press()) {
    INFO("KEY_EVENT key1 press.");
    ((void (*)())callback)();
    task_timed_key_react_new(key2_react, callback, STATUS_FREQ);
    return;
  }

  task_timed_key_react_new(key2_react, callback, 1);
}

void keyreact_init() {
  key1_react(key1_callback);
  key2_react(key2_callback);
}
