#include "step.h"
#include "../utils/utils.h"
#include "status.h"

void step_init(struct Step *step) {
  step->no = 0;
  step->len = 0;
}

void step_clear(struct Step *step) {
  step->no = 0;
  step->len = 0;
}

void step_push(struct Step *step, step_action action,
               step_next_condition next_condition) {
  if (step->len > STATUS_STEP_LIMIT) {
    THROW_WARN("STEP_PUSH_OVERFLOW len is %d, but STATUS_STEP_LIMIT is %d. "
               "Will ignore.",
               step->len, STATUS_STEP_LIMIT);
    return;
  }

  step->actions[step->len] = action;
  step->conditions[step->len] = next_condition;
  step->len += 1;
};

void step_next(struct Step *step, struct Status *sta) {
  step->no += 1;
  if (step->no >= step->len) {
    THROW_WARN("STEP_NEXT_OVERFLOW no is %d, but step->len is %d. Will ignore.",
               step->no, step->len);
    return;
  }

  step->actions[step->no](sta);
}

bool step_try_next(struct Step *step, struct Status *sta) {
  if (step->conditions[step->no](sta)) {
    step_next(step, sta);
    return true;
  }

  return false;
}

void action_turn_to_0(struct Status *sta) {
  INFO("STEP_TURN_TO_0");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 0.0;
  sta->base_speed = 0;
}

void action_turn_to_180(struct Status *sta) {
  INFO("STEP_TURN_TO_180");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 180.0;
  sta->base_speed = 0;
}

void action_turn_to_104(struct Status *sta) {
  INFO("STEP_TURN_TO_104");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 104.0;
  sta->base_speed = 0;
}

void action_turn_to_284(struct Status *sta){
  INFO("STEP_TURN_TO_284");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 284.0;
  sta->base_speed = 0;
}

void action_turn_to_256(struct Status *sta){
  INFO("STEP_TURN_TO_256");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 256.0;
  sta->base_speed = 0;
}

void action_keep_0(struct Status *sta) {
  INFO("STEP_KEEP_0");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 0.0;
  sta->base_speed = KEEP_ANGLE_SPEED;
}

void action_keep_180(struct Status *sta) {
  INFO("STEP_KEEP_180");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 180.0;
  sta->base_speed = KEEP_ANGLE_SPEED;
}

void action_keep_104(struct Status *sta) {
  INFO("STEP_KEEP_104");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 104.0;
  sta->base_speed = KEEP_ANGLE_SPEED;
}

void action_keep_284(struct Status *sta){
  INFO("STEP_KEEP_284");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 284.0;
  sta->base_speed = KEEP_ANGLE_SPEED;
}

void action_keep_256(struct Status *sta){
  INFO("STEP_KEEP_256");
  sta->mode.turn = true;
  sta->mode.follow = false;
  sta->dir.target = 256.0;
  sta->base_speed = KEEP_ANGLE_SPEED;
}

void action_follow(struct Status *sta) {
  INFO("STEP_FOLLOW");
  sta->mode.turn = false;
  sta->mode.follow = true;
  sta->base_speed = FOLLOW_LINE_SPEED;
}

void action_turn_left(struct Status *sta) {
  INFO("STEP_TURN_LEFT");
  sta->wheels[FONT_LEFT].target = -MAX_FOLLOW_TURN_SPEED;
  sta->wheels[FONT_RIGHT].target = MAX_FOLLOW_TURN_SPEED;
}

void action_turn_right(struct Status *sta) {
  INFO("STEP_TURN_RIGHT");
  sta->wheels[FONT_LEFT].target = MAX_FOLLOW_TURN_SPEED;
  sta->wheels[FONT_RIGHT].target = -MAX_FOLLOW_TURN_SPEED;
}

void action_stop(struct Status *sta) {
  INFO("STEP_STOP");
  sta->base_speed = 0;
}

void action_forward(struct Status *sta) {
  INFO("STEP_FORWARD");
  sta->base_speed = BASE_SPEED;
}

bool condition_turn_to(struct Status *sta) {
  float diff = sta->dir.target + sta->dir.origin - sta->sensor.gyro;
  diff = WARPPING(diff, -180.0, 180.0);
  return ABS(diff) <= TURN_ANGLE_RANGE;
}

bool condition_findline(struct Status *sta) {
  return sta->sensor.follow != ROAD_NO;
}

bool condition_roadless(struct Status *sta) {
  return sta->sensor.follow == ROAD_NO;
}

bool condition_never(struct Status *sta) { return false; }

bool condition_always(struct Status *sta) { return true; }
