#include "key.h"
#include "User/config.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "led.h"
#include "ti_msp_dl_config.h"

void key1_callback() {
  status.mode.record = true;
  status.mode.repeat = false;
  status.record_or_repeat_reference_time = status.times;
  led_blame(0, 2, 5, 5);
}

void key2_callback() {
  status.mode.repeat = true;
  status.mode.record = false;
  status.record_or_repeat_reference_time = status.times;
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
    ((void (*)())callback)();
    task_timed_key_react_new(key1_react, callback, TIMER1_FREQ);
    return;
  }

  task_timed_key_react_new(key1_react, callback, 1);
}

void key2_react(void *callback) {
  if (key2_is_press()) {
    ((void (*)())callback)();
    task_timed_key_react_new(key2_react, callback, TIMER1_FREQ);
    return;
  }

  task_timed_key_react_new(key2_react, callback, 1);
}

void keyreact_init() {
  key1_react(key1_callback);
  key2_react(key2_callback);
}
