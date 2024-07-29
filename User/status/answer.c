#include "answer.h"
#include "status.h"

void answer1(struct Status *sta) {
  step_clear(&sta->step);
  step_push(&sta->step, action_keep_0, condition_findline);
  step_push(&sta->step, action_stop, condition_never);
}

void answer2(struct Status *sta) {
  step_clear(&sta->step);
  step_push(&sta->step, action_keep_0, condition_findline);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_turn_to_180, condition_turn_to);
  step_push(&sta->step, action_keep_180, condition_findline);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_stop, condition_never);
}

void answer3(struct Status *sta) {
  step_clear(&sta->step);
  step_push(&sta->step, action_keep_0, condition_findline);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_turn_to_104, condition_turn_to);
  step_push(&sta->step, action_keep_104, condition_findline);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_stop, condition_never);
}
