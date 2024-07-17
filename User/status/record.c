#include "User/config.h"
#include "User/device/flash.h"
#include "User/task/task.h"
#include "stdbool.h"
#include "stdint.h"

#define RECORD_BUF_LEN ((PAGE_SIZE / 2) / sizeof(short))

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
  static struct Record record = {
      .data.which = false, .data.index = 0, .page = 0};

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

void status_record_force_swap_mem() {
  for (unsigned i = 0; i < 4 * RECORD_BUF_LEN; i++)
    status_record(0);
}

uint32_t record_task_buf_page_bitor_back_half;

void task_flash_erase(void *para) { flash_erase((unsigned)para); }

void task_flash_write(void *para) {
  unsigned short page = record_task_buf_page_bitor_back_half & 0xffff;
  bool back_half = record_task_buf_page_bitor_back_half & 0x80000000;

  flash_write_to(page, back_half ? RECORD_BUF_LEN * sizeof(short) : 0, para,
                 RECORD_BUF_LEN * sizeof(short));
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
