#include "key.h"
#include "User/config.h"
#include "User/status/record.h"
#include "User/status/status.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "led.h"
#include "ti_msp_dl_config.h"
#include "User/status/record.h"

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
