#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "../config.h"

// typedef struct Task Queue[TASK_QUEUE_LIMIT];

struct Queue {
  Task tasks[TASK_QUEUE_LIMIT];
  unsigned int head;
  unsigned int tail;
};

void task_queue_init(struct Queue *queue);
void task_queue_poll(struct Queue *queue);
void task_queue_push(struct Queue *queue, Task task);

#endif // !__QUEUE_H__
