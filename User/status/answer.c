#include "answer.h"
#include "../device/led.h"
#include "../utils/utils.h"
#include "User/status/step.h"
#include "answer4_step.h"
#include "status.h"

void answer_select(unsigned short which) {
  switch (which) {
  case 1:
    answer1(&status);
    break;
  case 2:
    answer2(&status);
    break;
  case 3:
    answer3(&status);
    break;
  case 4:
    answer4(&status);
    break;
  default:
    answer_do_nothing(&status);
    break;
  }
}

void answer_select_rpc(unsigned short var, void *para) {
  unsigned char which = var & 0xff;
  answer_select(which);
}

void answer1(struct Status *sta) {
  INFO("ANSWER1");
  step_clear(&sta->step);
  step_push_with_update(&sta->step, action_4_semicircle_start,
                        update_4_semicircle_start,
                        condition_4_semicircle_start);
  step_push_with_update(&sta->step, action_4_forward, update_4_forward,
                        condition_4_forward_stop_B_100cm);
  step_push(&sta->step, action_stop, condition_never);
}

void answer2(struct Status *sta) {
  INFO("ANSWER2");
  step_clear(&sta->step);
  step_push(&sta->step, action_keep_0,
            condition_findline_with_60000_75000_history_limit);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_keep_180,
            condition_findline_with_60000_75000_history_limit);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_stop, condition_never);
}

void answer3(struct Status *sta) {
  INFO("ANSWER3");
  step_clear(&sta->step);
  step_push(&sta->step, action_keep_0,
            condition_findline_with_80000_90000_history_limit_turn_left);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_keep_256,
            condition_findline_with_80000_90000_history_limit_turn_right);
  step_push(&sta->step, action_follow, condition_roadless);
  step_push(&sta->step, action_stop, condition_never);
}

#define STEP_PUSH(name)                                                        \
  step_push_with_update(&sta->step, action_4_##name, update_4_##name,          \
                        condition_4_##name)

void answer4(struct Status *sta) {
  INFO("ANSWER4");
  step_clear(&sta->step);

  //   for (int i = 0 ; i < 40; i++){
  //     STEP_PUSH(semicircle_enter);
  //   STEP_PUSH(arc_enter);
  //   }
  //     step_push(&sta->step, action_stop, condition_never);

  STEP_PUSH(semicircle_start);
  STEP_PUSH(arc_continue);

  for (int i = 0; i < 7; i++) {
    STEP_PUSH(forward);
    STEP_PUSH(arc_enter);
    STEP_PUSH(semicircle_match);
    /* STEP_PUSH(semicircle_match); */
    STEP_PUSH(arc_continue);
    /* STEP_PUSH(forward); */
  }

  STEP_PUSH(forward);
  STEP_PUSH(arc_enter);
  STEP_PUSH(semicircle_match);
  /* STEP_PUSH(semicircle_match); */
  step_push(&sta->step, action_stop, condition_never);
}

void answer4_bak(struct Status *sta) {
  INFO("ANSWER4");
  step_clear(&sta->step);
  //   step_push(&sta->step, action_turn_circle_right,
  //   condition_turn_circle_right_little);
  for (int i = 0; i < 4; i++) {
    /* step_push(&sta->step, action_keep_0,
     * condition_findline_with_80000_90000_history_limit_turn_left); */
    /* step_push(&sta->step, action_follow,
     * condition_roadless_with_3_least_limit); */
    /* step_push(&sta->step, action_turn_to_256, condition_turn_to); */
    /* step_push(&sta->step, action_keep_256,
     * condition_findline_with_80000_90000_history_limit_turn_right); */
    /* step_push(&sta->step, action_follow,
     * condition_roadless_with_3_least_limit); */
    /* step_push(&sta->step, action_turn_to_0, condition_turn_to); */
    step_push(&sta->step, action_forward, condition_forward_85000);
    step_push(&sta->step, action_turn_circle_left, condition_turn_circle_left);
    step_push(&sta->step, action_forward, condition_forward_85000);
    step_push(&sta->step, action_turn_circle_right,
              condition_turn_circle_right);
  }
  step_push(&sta->step, action_stop, condition_never);
}

void answer_do_nothing(struct Status *sta) {
  INFO("ANSWER_DO_NOTHING");
  step_clear(&sta->step);
  step_push(&sta->step, action_stop, condition_never);
}
