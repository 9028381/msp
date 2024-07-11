#include "../utils/log.h"
#include "stdlib.h"
#include "task.h"

void task_timed_init(struct Timed *timed) {
  INFO("TASK_TIMED_INIT.");

  timed->len = 0;
  timed->index = 0;
  timed->first = NULL;
  for (unsigned int i = 0; i < TASK_TIMED_LIMIT; i++) {
    timed->data[i].task.fn = NULL;
    timed->data[i].task.para = NULL;
    timed->data[i].next = NULL;
    timed->data[i].timed = 0;
  }
}

void task_timed_poll(struct Timed *timed) {
  unsigned int times = status.times;

  while (timed->first != NULL && timed->first->timed <= times) {
    task_call(timed->first->task);
    timed->first->task.fn = NULL;
    timed->len--;
    timed->first = timed->first->next;
  }
}

struct TimedTask *data_append(struct Timed *timed, struct TimedTask task) {
  if (timed->len >= TASK_TIMED_LIMIT) {
    THROW_WARN("TASK_TIMED_INSERT_ERROR tasks amount more than or equal to"
               " TASK_TIMED_LIMIT. Will ignore.");
    return NULL;
  }

  while (timed->data[timed->index].task.fn != NULL)
    timed->index = (timed->index + 1) % TASK_TIMED_LIMIT;

  timed->data[timed->index] = task;
  timed->len++;
  return &timed->data[timed->index];
}

void task_timed_insert(struct Timed *timed, Task task, unsigned int time) {
  struct TimedTask *data = data_append(
      timed, (struct TimedTask){.task = task, .timed = time, .next = NULL});

  if (data == NULL)
    return;

  if (timed->first == NULL) {
    timed->first = data;
    return;
  }

  struct TimedTask *current = timed->first;
  while (current->next != NULL) {
    if (current->timed >= data->timed) {
      data->next = current->next;
      current->next = data;
      return;
    }

    current = current->next;
  }
}
