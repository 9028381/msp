#include "answer.h"
#include "../device/led.h"
#include "../utils/utils.h"
#include "User/status/step.h"
#include "answer_step.h"
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
  case 5:
    answer4_fast(&status);
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
  step_push(&sta->step, action_led_blink, condition_always);

  // A -> B
  step_push(&sta->step, action_forward_slow, condition_forward_stop_B_100cm);
  step_push(&sta->step, action_led_blink, condition_always);

  step_push(&sta->step, action_stop, condition_never);
}

void answer2(struct Status *sta) {
  INFO("ANSWER2");
  step_clear(&sta->step);
  step_push(&sta->step, action_led_blink, condition_always);

  // A -> B
  step_push(&sta->step, action_forward_slow, condition_forward_stop_B_100cm);
  step_push(&sta->step, action_led_blink, condition_always);

  // B -> C
  step_push_with_update(&sta->step, action_2_semicircle_enter,
                        update_2_semicircle_enter,
                        condition_2_semicircle_enter);
  step_push_with_update(&sta->step, action_2_semicircle_match,
                        update_2_semicircle_match,
                        condition_2_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  // C -> D
  step_push(&sta->step, action_forward_slow, condition_forward_stop_B_100cm);
  step_push(&sta->step, action_led_blink, condition_always);

  // D -> A
  step_push_with_update(&sta->step, action_2_semicircle_enter,
                        update_2_semicircle_enter,
                        condition_2_semicircle_enter);
  step_push_with_update(&sta->step, action_2_semicircle_match2,
                        update_2_semicircle_match2,
                        condition_2_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  step_push(&sta->step, action_stop, condition_never);
}

#define STEP_PUSH(name)                                                        \
  step_push_with_update(&sta->step, action_4_##name, update_4_##name,          \
                        condition_4_##name)

void answer3(struct Status *sta) {
  INFO("ANSWER3");
  step_clear(&sta->step);
  step_push(&sta->step, action_led_blink, condition_always);

  // A -> C
  step_push(&sta->step, action_arc_start, condition_arc_start);
  /* step_push(&sta->step, action_arc_continue1, condition_arc_continue1); */
  step_push(&sta->step, action_forward_normal, condition_forward1_limit);
  step_push(&sta->step, action_arc_enter1, condition_arc_enter1);
  step_push(&sta->step, action_led_blink, condition_always);

  // C -> B
  step_push_with_update(&sta->step, action_semicircle_enter1,
                        update_semicircle_enter1, condition_semicircle_enter);
  step_push_with_update(&sta->step, action_semicircle_match1,
                        update_semicircle_match1, condition_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  // B -> D
  step_push(&sta->step, action_arc_continue2, condition_arc_continue2);
  step_push(&sta->step, action_forward_normal, condition_forward2_limit);
  step_push(&sta->step, action_arc_enter2, condition_arc_enter2);
  step_push(&sta->step, action_led_blink, condition_always);

  // D -> A
  step_push_with_update(&sta->step, action_semicircle_enter2,
                        update_semicircle_enter2, condition_semicircle_enter);
  step_push_with_update(&sta->step, action_semicircle_match2,
                        update_semicircle_match2, condition_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  step_push(&sta->step, action_stop, condition_never);
}

bool condition_gw_read_road(struct Status *sta) {
  return sta->sensor.follow_gw != ROAD_NO;
}

void answer4(struct Status *sta) {
  INFO("ANSWER4");
  step_clear(&sta->step);
  step_push(&sta->step, action_led_blink, condition_always);

  // test circle
  //   step_push_with_update(&sta->step, action_semicircle_start,
  //                       update_semicircle_start, condition_semicircle_start);
  //                       for(int i = 0; i < 30 ; i++){
  //                           step_push(&sta->step, action_arc_continue1,
  //                           condition_gw_read_road);
  //                               step_push_with_update(&sta->step,
  //                               action_semicircle_enter2,
  //                         update_semicircle_enter2,
  //                         condition_semicircle_enter);
  //   step_push_with_update(&sta->step, action_semicircle_match2,
  //   update_semicircle_match2, condition_semicircle_match);

  //                       }
  //                         step_push(&sta->step, action_stop,
  //                         condition_never);

  // A -> C
  step_push(&sta->step, action_arc_start, condition_arc_start);
  /* step_push_with_update(&sta->step, action_semicircle_start, */
  /*                       update_semicircle_start, condition_semicircle_start);
   */
  /* step_push(&sta->step, action_arc_continue1, condition_arc_continue1); */
  step_push(&sta->step, action_forward_normal, condition_forward1_limit);
  step_push(&sta->step, action_arc_enter1, condition_arc_enter1);
  step_push(&sta->step, action_led_blink, condition_always);

  for (int i = 0; i < 3; i++) {
    // C -> B
    step_push_with_update(&sta->step, action_semicircle_enter1,
                          update_semicircle_enter1, condition_semicircle_enter);
    step_push_with_update(&sta->step, action_semicircle_match1,
                          update_semicircle_match1, condition_semicircle_match);
    step_push(&sta->step, action_led_blink, condition_always);

    // B -> D
    step_push(&sta->step, action_arc_continue2, condition_arc_continue2);
    step_push(&sta->step, action_forward_normal, condition_forward2_limit);
    step_push(&sta->step, action_arc_enter2, condition_arc_enter2);
    step_push(&sta->step, action_led_blink, condition_always);

    // D -> A
    step_push_with_update(&sta->step, action_semicircle_enter2,
                          update_semicircle_enter2, condition_semicircle_enter);
    step_push_with_update(&sta->step, action_semicircle_match2,
                          update_semicircle_match2, condition_semicircle_match);
    step_push(&sta->step, action_led_blink, condition_always);

    // A -> C
    step_push(&sta->step, action_arc_continue1, condition_arc_continue1);
    step_push(&sta->step, action_forward_normal, condition_forward1_limit);
    step_push(&sta->step, action_arc_enter1, condition_arc_enter1);
    step_push(&sta->step, action_led_blink, condition_always);
  }

  // C -> B
  step_push_with_update(&sta->step, action_semicircle_enter1,
                        update_semicircle_enter1, condition_semicircle_enter);
  step_push_with_update(&sta->step, action_semicircle_match1,
                        update_semicircle_match1, condition_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  // B -> D
  step_push(&sta->step, action_arc_continue2, condition_arc_continue2);
  step_push(&sta->step, action_forward_normal, condition_forward2_limit);
  step_push(&sta->step, action_arc_enter2, condition_arc_enter2);
  step_push(&sta->step, action_led_blink, condition_always);

  // D -> A
  step_push_with_update(&sta->step, action_semicircle_enter2,
                        update_semicircle_enter2, condition_semicircle_enter);
  step_push_with_update(&sta->step, action_semicircle_match2,
                        update_semicircle_match2, condition_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  step_push(&sta->step, action_stop, condition_never);
}

void answer4_fast(struct Status *sta) {
  INFO("ANSWER4_FAST");
  step_clear(&sta->step);
  step_push(&sta->step, action_led_blink, condition_always);

    // for(int i = 0; i < 30 ; i++){
    //     step_push(&sta->step, action_arc_continue1, condition_gw_read_road);
    //     step_push_with_update(&sta->step, action_semicircle_enter2_fast, update_semicircle_enter2_fast, condition_semicircle_enter);
    //     step_push_with_update(&sta->step, action_semicircle_match2_fast, update_semicircle_match2_fast, condition_semicircle_match);
    // }
    // step_push(&sta->step, action_stop, condition_never);


  // A -> C
  step_push(&sta->step, action_arc_start, condition_arc_start);
  /* step_push_with_update(&sta->step, action_semicircle_start, */
  /*                       update_semicircle_start, condition_semicircle_start);
   */
  /* step_push(&sta->step, action_arc_continue1_fast, condition_arc_continue1);
   */
  step_push(&sta->step, action_forward_fast, condition_forward1_limit);
  step_push(&sta->step, action_arc_enter1_fast, condition_arc_enter1);
  step_push(&sta->step, action_led_blink, condition_always);

  for (int i = 0; i < 3; i++) {
    // C -> B
    step_push_with_update(&sta->step, action_semicircle_enter1_fast,
                          update_semicircle_enter1_fast,
                          condition_semicircle_enter);
    step_push_with_update(&sta->step, action_semicircle_match1_fast,
                          update_semicircle_match1_fast,
                          condition_semicircle_match);
    step_push(&sta->step, action_led_blink, condition_always);

    // B -> D
    step_push(&sta->step, action_arc_continue2_fast, condition_arc_continue2);
    step_push(&sta->step, action_forward_fast, condition_forward2_limit);
    step_push(&sta->step, action_arc_enter2_fast, condition_arc_enter2);
    step_push(&sta->step, action_led_blink, condition_always);

    // D -> A
    step_push_with_update(&sta->step, action_semicircle_enter2_fast,
                          update_semicircle_enter2_fast,
                          condition_semicircle_enter);
    step_push_with_update(&sta->step, action_semicircle_match2_fast,
                          update_semicircle_match2_fast,
                          condition_semicircle_match);
    step_push(&sta->step, action_led_blink, condition_always);

    // A -> C
    step_push(&sta->step, action_arc_continue1_fast, condition_arc_continue1);
    step_push(&sta->step, action_forward_fast, condition_forward1_limit);
    step_push(&sta->step, action_arc_enter1_fast, condition_arc_enter1);
    step_push(&sta->step, action_led_blink, condition_always);
  }

  // C -> B
  step_push_with_update(&sta->step, action_semicircle_enter1_fast,
                        update_semicircle_enter1_fast,
                        condition_semicircle_enter);
  step_push_with_update(&sta->step, action_semicircle_match1_fast,
                        update_semicircle_match1_fast,
                        condition_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  // B -> D
  step_push(&sta->step, action_arc_continue2_fast, condition_arc_continue2);
  step_push(&sta->step, action_forward_fast, condition_forward2_limit);
  step_push(&sta->step, action_arc_enter2_fast, condition_arc_enter2);
  step_push(&sta->step, action_led_blink, condition_always);

  // D -> A
  step_push_with_update(&sta->step, action_semicircle_enter2_fast,
                        update_semicircle_enter2_fast,
                        condition_semicircle_enter);
  step_push_with_update(&sta->step, action_semicircle_match2_fast,
                        update_semicircle_match2_fast,
                        condition_semicircle_match);
  step_push(&sta->step, action_led_blink, condition_always);

  step_push(&sta->step, action_stop, condition_never);
}

void answer_do_nothing(struct Status *sta) {
  INFO("ANSWER_DO_NOTHING");
  step_clear(&sta->step);
  step_push(&sta->step, action_led_blink, condition_always);
  step_push(&sta->step, action_stop, condition_never);
}
