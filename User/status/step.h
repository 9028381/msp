#ifndef __STEP_H__
#define __STEP_H__

#include "../config.h"

struct Status;

typedef void (*step_fn)(struct Status *sta);
struct Step {
  unsigned no;
  unsigned len;
  step_fn fn[STATUS_STEP_LIMIT];
};

void step_init(struct Step *step);
void step_push(struct Step *step, step_fn fn);
void step_next(struct Step *step, struct Status *sta);

/// <-
void step_turn_left(struct Status *sta);

/// ->
void step_turn_right(struct Status *sta);

void step_stop(struct Status *sta);
void step_forward(struct Status *sta);

#endif // !__STEP_H__
