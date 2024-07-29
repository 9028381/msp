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

#define DECLARE_ACTION_TURN_TO(angle)                                          \
  void action_turn_to_##angle(struct Status *sta);

#define DECLARE_ACTION_KEEP(angle) void action_keep_##angle(struct Status *sta);

DECLARE_ACTION_KEEP(0)
DECLARE_ACTION_KEEP(180)
DECLARE_ACTION_KEEP(103)
DECLARE_ACTION_KEEP(257)
DECLARE_ACTION_KEEP(256)
DECLARE_ACTION_KEEP(255)

DECLARE_ACTION_TURN_TO(0)
DECLARE_ACTION_TURN_TO(180)
DECLARE_ACTION_TURN_TO(103)
DECLARE_ACTION_TURN_TO(257)
DECLARE_ACTION_TURN_TO(256)
DECLARE_ACTION_TURN_TO(255)

void action_do_nothing(struct Status *sta);

bool condition_turn_to(struct Status *sta);

bool condition_findline(struct Status *sta);
bool condition_findline_with_3_least_limit(struct Status *sta);
bool condition_findline_with_60000_75000_history_limit(struct Status *sta);
bool condition_findline_with_80000_90000_history_limit(struct Status *sta);
bool condition_findline_with_80000_90000_history_limit_turn_left(
    struct Status *sta);
bool condition_findline_with_80000_90000_history_limit_turn_right(
    struct Status *sta);

bool condition_roadless(struct Status *sta);
bool condition_roadless_with_3_least_limit(struct Status *sta);

bool condition_never(struct Status *sta);
bool condition_always(struct Status *sta);

void action_turn_circle_left(struct Status *sta);
void action_turn_circle_right(struct Status *sta);
bool condition_turn_circle_left(struct Status *sta);
bool condition_turn_circle_right(struct Status *sta);
bool condition_forward_85000(struct Status *sta);

#endif // !__STEP_H__
