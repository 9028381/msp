#ifndef __TASK_H__
#define __TASK_H__

struct Task {
  void (*fn)(void *para);
  void *para;
};
typedef struct Task Task;

Task task_new(void (*fn)(void *para), void *para);
void task_call(Task task);

#include "queue.h"
#include "rpc.h"
#include "timed.h"

struct TaskSystem {
  RPC rpc;
  struct Queue queue;
  struct Timed timed;
};

extern struct TaskSystem task;

void task_init(struct TaskSystem *task);
void task_poll(struct TaskSystem *task);

#endif // !__TASK_H__
