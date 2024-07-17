#include "key.h"
#include "User/config.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "ti_msp_dl_config.h"

void key1_callback() {
  status.mode.record = true;
  status.mode.repeat = false;
  status.record_or_repeat_reference_time = status.times;
}

void key2_callback() {
  status.mode.repeat = true;
  status.mode.record = false;
  status.record_or_repeat_reference_time = status.times;
}

bool key1_is_press() { return !DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN); }
bool key2_is_press() { return !DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN); }

void task_timed_key_react_new(void (*key_react)(void *), unsigned later) {
  Task t = task_new(key_react, NULL);
  task_timed_append(&task.timed, t, later);
}

void key1_react(void *_) {
  if (key1_is_press()) {
    key1_callback();
    task_timed_key_react_new(key1_react, TIMER1_FREQ);
    return;
  }

  task_timed_key_react_new(key1_react, 1);
}

void key2_react(void *_) {
  if (key2_is_press()) {
    key2_callback();
    task_timed_key_react_new(key2_react, TIMER1_FREQ);
    return;
  }

  task_timed_key_react_new(key2_react, 1);
}

void keyreact_init() {
  key1_react(NULL);
  key2_react(NULL);
}
