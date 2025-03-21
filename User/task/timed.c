#include "../utils/log.h"
#include "stdlib.h"
#include "task.h"

void task_timed_init(struct Timed *timed) {
  INFO("TASK_TIMED_INIT");

  timed->len = 0;
  timed->index = 0;
  timed->first = NULL;
  for (unsigned int i = 0; i < TASK_TIMED_LIMIT; i++)
    timed->data[i].task.fn = NULL;
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

void task_timed_insert_task_queue_later(void *para) {
  struct Timed *timed = &task.timed;
  struct TimedTask *data = para;

  if (data == NULL)
    return;

  if (timed->first == NULL) {
    timed->first = data;
    return;
  }

  if (timed->first->timed >= data->timed) {
    data->next = timed->first;
    timed->first = data;
    return;
  }

  struct TimedTask *current = timed->first;

  while (current->next != NULL) {
    if (current->next->timed >= data->timed) {
      data->next = current->next;
      current->next = data;
      return;
    }

    current = current->next;
  }

  current->next = data;
}

void task_timed_insert(struct Timed *timed, Task timedtask, unsigned int time) {
  struct TimedTask *data = data_append(
      timed,
      (struct TimedTask){.task = timedtask, .timed = time, .next = NULL});
  Task t = task_new(task_timed_insert_task_queue_later, data);
  task_queue_push(&task.queue, t);
}

void task_timed_append(struct Timed *timed, Task task, unsigned int later) {
  unsigned int time = status.times + later;
  task_timed_insert(timed, task, time);
}
