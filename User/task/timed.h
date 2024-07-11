#ifndef __TIMED_H__
#define __TIMED_H__

#include "../config.h"

struct TimedTask {
  Task task;
  unsigned int timed;
  struct TimedTask *next;
};

struct Timed {
  unsigned int len;
  unsigned int index;
  struct TimedTask *first;
  struct TimedTask data[TASK_TIMED_LIMIT];
};

void task_timed_init(struct Timed *timed);
void task_timed_poll(struct Timed *timed);
void task_timed_insert(struct Timed *timed, Task task, unsigned int time);

#endif // !__TIMED_H__
