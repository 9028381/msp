#ifndef __STEP_H__
#define __STEP_H__

#include "../config.h"
#include "../device/wheel.h"
#include "stdbool.h"

struct Status;

typedef void (*step_action)(struct Status *sta);
typedef bool (*step_next_condition)(struct Status *sta);

struct StepContext {
  unsigned start_time;
  unsigned start_history[WHEEL_NUMS];
};

struct Step {
  unsigned no;
  unsigned len;
  step_action actions[STATUS_STEP_LIMIT];
  step_next_condition conditions[STATUS_STEP_LIMIT];
  struct StepContext ctx;
};

void step_init(struct Step *step);
void step_clear(struct Step *step);

void step_push(struct Step *step, step_action action,
               step_next_condition next_condition);
bool step_try_next(struct Step *step, struct Status *sta);

/// <-
void action_turn_left(struct Status *sta);
/// ->
void action_turn_right(struct Status *sta);
void action_stop(struct Status *sta);
void action_forward(struct Status *sta);

void action_follow(struct Status *sta);

void action_keep_0(struct Status *sta);
void action_keep_180(struct Status *sta);
void action_keep_104(struct Status *sta);
void action_keep_284(struct Status *sta);
void action_keep_256(struct Status *sta);

void action_turn_to_0(struct Status *sta);
void action_turn_to_180(struct Status *sta);
void action_turn_to_104(struct Status *sta);
void action_turn_to_284(struct Status *sta);
void action_turn_to_256(struct Status *sta);

void action_do_nothing(struct Status *sta);

bool condition_turn_to(struct Status *sta);
bool condition_findline(struct Status *sta);
bool condition_roadless(struct Status *sta);

bool condition_never(struct Status *sta);
bool condition_always(struct Status *sta);

#endif // !__STEP_H__
