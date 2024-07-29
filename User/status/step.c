#include "step.h"
#include "../utils/utils.h"
#include "status.h"

void step_init(struct Step *step) {
  step->no = 0;
  step->len = 0;
  step->ctx.start_time = 0;
  for (int i = 0; i < WHEEL_NUMS; i++)
    step->ctx.start_history[i] = 0;
  step_push(step, action_do_nothing, condition_always);
}

void step_ctx_next(struct StepContext *ctx, struct Status *sta) {
  ctx->start_time = sta->times;
  for (int i = 0; i < WHEEL_NUMS; i++)
    ctx->start_history[i] = sta->wheels[i].history;
}

void step_ctx_display(struct StepContext *ctx, struct Status *sta) {
  INFO("STEP_CTX_DISPLAY");
  INFO("  start_time=%d, duration_time=%d", ctx->start_time,
       sta->times - ctx->start_time);
  for (int i = 0; i < WHEEL_NUMS; i++) {
    INFO("  start_history[%d]=%d, duration_history[%d]=%d", i,
         ctx->start_history[i], i,
         sta->wheels[i].history - ctx->start_history[i]);
  }
}

void step_clear(struct Step *step) { step_init(step); }

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

  INFO("STEP_NEXT %d", step->no);
  step_ctx_display(&step->ctx, sta);
  step_ctx_next(&step->ctx, sta);
  step->actions[step->no](sta);
}

bool step_try_next(struct Step *step, struct Status *sta) {
  if (step->conditions[step->no](sta)) {
    step_next(step, sta);
    return true;
  }

  return false;
}

#define ACTION_TURN_TO(angle)                                                  \
  void action_turn_to_##angle(struct Status *sta) {                            \
    INFO("STEP_TURN_TO_" #angle);                                              \
    sta->mode.turn = true;                                                     \
    sta->mode.follow = false;                                                  \
    sta->dir.target = angle;                                                   \
    sta->base_speed = 0;                                                       \
  }

ACTION_TURN_TO(0)
ACTION_TURN_TO(180)
ACTION_TURN_TO(103)
ACTION_TURN_TO(257)
ACTION_TURN_TO(256)
ACTION_TURN_TO(255)

#define ACTION_KEEP(angle)                                                     \
  void action_keep_##angle(struct Status *sta) {                               \
    INFO("STEP_KEEP_" #angle);                                                 \
    sta->mode.turn = true;                                                     \
    sta->mode.follow = false;                                                  \
    sta->dir.target = angle;                                                   \
    sta->base_speed = TURN_ANGLE_SPEED;                                        \
  }

ACTION_KEEP(0)
ACTION_KEEP(180)
ACTION_KEEP(103)
ACTION_KEEP(257)
ACTION_KEEP(256)
ACTION_KEEP(255)

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

void action_do_nothing(struct Status *sta) { INFO("STEP_DO_NOTHING"); }

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

bool condition_findline_with_3_least_limit(struct Status *sta) {
  static unsigned char times = 0;
  times += condition_findline(sta) ? 1 : 0;
  if (times <= 3)
    return false;

  times = 0;
  return true;
}

bool condition_roadless_with_3_least_limit(struct Status *sta) {
  static unsigned char times = 0;
  times += condition_roadless(sta) ? 1 : 0;
  if (times <= 3)
    return false;

  times = 0;
  return true;
}


bool condition_findline_with_60000_75000_history_limit(struct Status *sta) {
  int history_left =
      sta->wheels[FONT_LEFT].history - sta->step.ctx.start_history[FONT_LEFT];
  int history_right =
      sta->wheels[FONT_RIGHT].history - sta->step.ctx.start_history[FONT_RIGHT];

  if (history_left < 60000 || history_right < 60000)
    return false;

  if (history_left > 75000 || history_right > 75000)
    return true;

  return condition_findline(sta);
}

bool condition_findline_with_80000_90000_history_limit(struct Status *sta) {
  int history_left =
      sta->wheels[FONT_LEFT].history - sta->step.ctx.start_history[FONT_LEFT];
  int history_right =
      sta->wheels[FONT_RIGHT].history - sta->step.ctx.start_history[FONT_RIGHT];

  if (history_left < 80000 || history_right < 80000)
    return false;

  if (history_left > 90000 || history_right > 90000)
    return true;

  return condition_findline(sta);
}

bool condition_findline_with_80000_90000_history_limit_turn_left(
    struct Status *sta) {
  int history_left =
      sta->wheels[FONT_LEFT].history - sta->step.ctx.start_history[FONT_LEFT];
  int history_right =
      sta->wheels[FONT_RIGHT].history - sta->step.ctx.start_history[FONT_RIGHT];

  if (history_left < 80000 || history_right < 80000)
    return false;
  else
     sta->base_speed = FOLLOW_LINE_SPEED;

  if (history_left > 90000 || history_right > 90000) {
    if (sta->sensor.follow != ROAD_NO)
      return true;

    sta->mode.turn = false;
    sta->mode.follow = true;
    sta->sensor.follow = 400;
    return false;
  }

  return condition_findline(sta);
}

bool condition_findline_with_80000_90000_history_limit_turn_right(
    struct Status *sta) {
  int history_left =
      sta->wheels[FONT_LEFT].history - sta->step.ctx.start_history[FONT_LEFT];
  int history_right =
      sta->wheels[FONT_RIGHT].history - sta->step.ctx.start_history[FONT_RIGHT];

  if (history_left < 80000 || history_right < 80000)
    return false;
  else 
    sta->base_speed = FOLLOW_LINE_SPEED;

  if (history_left > 90000 || history_right > 90000) {
    if (sta->sensor.follow != ROAD_NO)
      return true;

    sta->mode.turn = false;
    sta->mode.follow = true;
    sta->sensor.follow = -400;
    return false;
  }

  return condition_findline(sta);
}

bool condition_never(struct Status *sta) { return false; }

bool condition_always(struct Status *sta) { return true; }
