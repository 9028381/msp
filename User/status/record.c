#include "User/config.h"
#include "User/device/flash.h"
#include "User/device/led.h"
#include "User/task/task.h"
#include "User/utils/utils.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"

#define RECORD_BUF_LEN ((PAGE_SIZE / 2) / sizeof(int))

struct RecordDataAB {
  int ab[2][RECORD_BUF_LEN];
  bool which; // false: A, true: B
  unsigned index;
};

struct Record {
  struct RecordDataAB data;
  unsigned page;
};

void task_queue_push_flash_erase(unsigned page);
void task_queue_push_flash_write(unsigned char page, const void *src,
                                 bool back_half);

void status_record(int var) {
  static bool is_first = true;
  static struct Record record = {
      .data.which = false, .data.index = 0, .page = 0};

  record.data.ab[record.data.which][record.data.index] = var;
  record.data.index += 1;

  if (record.data.index >= RECORD_BUF_LEN) {
    if (is_first) {
      task_queue_push_flash_erase(0);
      is_first = false;
    }

    task_queue_push_flash_write(record.page, &record.data.ab[record.data.which],
                                record.data.which);
    // data B end need new flash page
    if (record.data.which) {
      record.page += 1;
      task_queue_push_flash_erase(record.page);
    }

    record.data.which = !record.data.which;
    record.data.index = 0;
  }
}

void status_record_force_swap_mem() {
  for (unsigned i = 0; i < RECORD_BUF_LEN; i++)
    status_record(0);
}

uint32_t record_task_buf_page_bitor_back_half;

void task_flash_erase(void *para) { flash_erase((unsigned)para); }

void task_flash_write(void *para) {
  unsigned short page = record_task_buf_page_bitor_back_half & 0xffff;
  bool back_half = record_task_buf_page_bitor_back_half & 0x80000000;

  flash_write_to(page, back_half ? RECORD_BUF_LEN * sizeof(int) : 0, para,
                 RECORD_BUF_LEN * sizeof(int));
}

void task_queue_push_flash_erase(unsigned page) {
  Task t = task_new(task_flash_erase, (void *)page);
  task_queue_push(&task.queue, t);
}

void task_queue_push_flash_write(unsigned char page, const void *src,
                                 bool back_half) {
  record_task_buf_page_bitor_back_half = page;
  record_task_buf_page_bitor_back_half |= back_half ? 0x80000000 : 0;

  Task t = task_new(task_flash_write, (void *)src);
  task_queue_push(&task.queue, t);
}

void record_once_switch(unsigned short var, void *para) {
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
    flash_erase(PAGE_NUM - 1);
    flash_write(PAGE_NUM - 1, &status.rec.duration,
                sizeof(status.rec.duration));
    status_record_force_swap_mem();
    led_blame(0, 2, 10, 10);
  }
}

void repeat_auto_stop(void *para) {
  INFO("Stop repeat");
  status.mode.repeat = false;
  led_blame(0, 5, 10, 10);
}

void repeat_open(unsigned short var, void *para) {
  INFO("Start repeat");
  status.mode.repeat = true;
  status.rec.times = status.times;
  for (int i = 0; i < WHEEL_NUMS; i++)
    status.rec.wheels_history[i] = status.wheels[i].history;
  led_blame(0, 2, 10, 10);
  Task t = task_new(repeat_auto_stop, NULL);
  task_timed_append(&task.timed, t, status.rec.duration - 1);
}
