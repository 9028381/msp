#include "task.h"
#include "../utils/log.h"
#include "stdlib.h"

struct TaskSystem task;

void task_init(struct TaskSystem *task) {
  INFO("TASK_SYSTEM_INIT");

  task_rpc_init(task->rpc);
  task_queue_init(&task->queue);
  task_timed_init(&task->timed);
}

void task_poll(struct TaskSystem *task) {
  task_timed_poll(&task->timed);
  task_queue_poll(&task->queue);
}

Task task_new(void (*fn)(void *para), void *para) {
  if (fn == NULL)
    THROW_ERROR("TASK_NEW_ERROR fn is NULL.");

  Task task = {.fn = fn, .para = para};
  return task;
}

void task_call(Task task) {
  if (task.fn == NULL)
    THROW_WARN("TASK_CALL_ERROR task fn points NULL");

  task.fn(task.para);
}
