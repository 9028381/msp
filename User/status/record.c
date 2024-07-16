#include "User/config.h"
#include "User/device/flash.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "stdbool.h"
#include "stdint.h"

#define RECORD_BUF_LEN ((PAGE_SIZE / 2) / sizeof(int32_t))

struct RecordDataAB {
  int32_t ab[2][RECORD_BUF_LEN];
  bool which; // false: A, true: B
  unsigned index;
};

struct Record {
  struct RecordDataAB data;
  unsigned page;
};

void status_record_init() { flash_erase(0); }

void task_queue_push_flash_erase(unsigned page);
void task_queue_push_flash_write(unsigned char page, const void *src,
                                 bool back_half);

void status_record(int var) {
  static struct Record record = {.data.which = false, .data.index = 0, .page = 0};

  record.data.ab[record.data.which][record.data.index] = var;
  record.data.index += 1;

  if (record.data.index >= RECORD_BUF_LEN) {
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

void task_flash_erase(void *para) { flash_erase((unsigned)para); }

void task_flash_write(void *para) {
  unsigned int data = (unsigned int)para;
  unsigned short page = (data >> 24) & 0x7f;
  void *src = (void *)(data & 0x00ffffff);
  bool back_half = data & 0x80000000;

  flash_write_to(page, back_half ? RECORD_BUF_LEN : 0, src,
                 RECORD_BUF_LEN * sizeof(int32_t));
}

void task_queue_push_flash_erase(unsigned page) {
  Task t = task_new(task_flash_erase, (void *)page);
  task_queue_push(&task.queue, t);
}

void task_queue_push_flash_write(unsigned char page, const void *src,
                                 bool back_half) {
  uint32_t para = (uint32_t)src;
  if (para & 0xff000000) {
    THROW_WARN("RECORD_ERROR: para & 0xff000000 is not 0. para = %#0x."
               " Can't zip with page",
               para);
    return;
  }
  para = page << 24 | para;
  para = page | (back_half ? 0x80000000 : 0);

  Task t = task_new(task_flash_write, (void *)para);
  task_queue_push(&task.queue, t);
}
