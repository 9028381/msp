#include "../utils/log.h"
#include "task.h"
#include "User/device/cam.h"

void task_queue_init(struct Queue *queue) {
  INFO("TASK_QUEUE_INIT.");

  queue->head = 0;
  queue->tail = 0;
}

inline unsigned int queue_len(struct Queue *queue) {
  return queue->tail - queue->head;
}

inline unsigned int queue_wrapping(unsigned int position) {
  return position % TASK_QUEUE_LIMIT;
}

inline void queue_insert(Task queue[TASK_QUEUE_LIMIT], unsigned int position,
                         Task task) {
  position = queue_wrapping(position);
  queue[position] = task;
}

void task_queue_poll(struct Queue *queue) {
  if (queue_len(queue) == 0)
    return;

  unsigned int index = queue_wrapping(queue->head);
  task_call(queue->tasks[index]);

  queue->head++;
};

void task_queue_push(struct Queue *queue, Task task) {
  if (queue_len(queue) >= TASK_QUEUE_LIMIT) {
    THROW_WARN("TASK_QUEUE_FULL. will ignore this task.");
    return;
  }

  queue_insert(queue->tasks, queue->tail, task);

  queue->tail++;
};
