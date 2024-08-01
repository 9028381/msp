#include "answer_step.h"
#include "../device/led.h"
#include "../utils/log.h"
#include "User/device/wheel.h"
#include "status.h"

struct DurationHistory {
  int left;
  int right;
};
struct DurationHistory duration_history_get(struct Status *sta) {
  struct DurationHistory history;
  history.left =
      sta->wheels[FONT_LEFT].history - sta->step.ctx.start_history[FONT_LEFT];
  history.right =
      sta->wheels[FONT_RIGHT].history - sta->step.ctx.start_history[FONT_RIGHT];
  return history;
}
int duration_history_sum(struct DurationHistory *history) {
  return history->left + history->right;
}
struct SpeedCache {
  int left;
  int right;
};
// struct SpeedCache speed_cache = {.left = 560, .right = 410}; // 520 700
struct SpeedCache speed_cache = {.left = 200, .right = 144}; // 520 700

void speed_cache_recover(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = speed_cache.left;
  sta->wheels[FONT_RIGHT].target = speed_cache.right;
}
void speed_cache_rev() {
  int tmp = speed_cache.left;
  speed_cache.left = speed_cache.right;
  speed_cache.right = tmp;
}
void speed_cache_store(struct Status *sta) {
  speed_cache.left = sta->wheels[FONT_LEFT].target;
  speed_cache.right = sta->wheels[FONT_RIGHT].target;
}

/// semicircle_start
void action_semicircle_start(struct Status *sta) {
  INFO("ACTION_4_SEMICIRCLE_START");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
}

void update_semicircle_start(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;

  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}

bool condition_semicircle_start(struct Status *sta) {
  return sta->sensor.follow_ms == ROAD_NO;
}

/// forward
void action_4_forward(struct Status *sta) {
  INFO("ACTION_4_FORWARD");
  speed_cache_rev();
  sta->wheels[FONT_LEFT].target = 560;
  sta->wheels[FONT_RIGHT].target = 560;
}

void update_4_forward(struct Status *sta) {}

bool condition_4_forward(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  return history.left + history.right > 80000;
}

void action_forward_slow(struct Status *sta) {
  INFO("ACTION_1_FORWARD");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.forward_speed[SpeedSlow];
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.forward_speed[SpeedSlow];
}

void action_forward_normal(struct Status *sta) {
  INFO("ACTION_FORWARD_NORMAL");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.forward_speed[SpeedNorm];
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.forward_speed[SpeedNorm];
}

void action_forward_fast(struct Status *sta) {
  INFO("ACTION_FORWARD_FAST");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.forward_speed[SpeedFast];
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.forward_speed[SpeedFast];
}

bool condition_forward1_limit(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;
  return sum > sta->cheat_sheet.forward1;
}

bool condition_forward2_limit(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;
  return sum > sta->cheat_sheet.forward2;
}

bool condition_forward_stop_B_100cm(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;
  return sum > sta->cheat_sheet.AtoB.min &&
         (sum > sta->cheat_sheet.AtoB.max || sta->sensor.follow_gw != ROAD_NO);
}

/// arc_enter
void action_arc_enter1(struct Status *sta) {
  INFO("ACTION_ARC_ENTER1");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
}

void action_arc_enter1_fast(struct Status *sta) {
  INFO("ACTION_ARC_ENTER1");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
}

bool condition_arc_enter1(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;

  if (sum < sta->cheat_sheet.arc_enter1.min)
    return false;

  if (sta->sensor.follow_gw != ROAD_NO)
    return true;

  if (sum > sta->cheat_sheet.arc_enter1.max)
    return true;

  // try to recover
  return false;
}

void action_arc_enter2(struct Status *sta) {
  INFO("ACTION_ARC_ENTER2");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
}
void action_arc_enter2_fast(struct Status *sta) {
  INFO("ACTION_ARC_ENTER2_FAST");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
}

bool condition_arc_enter2(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;

  if (sum < sta->cheat_sheet.arc_enter2.min)
    return false;

  if (sta->sensor.follow_gw != ROAD_NO)
    return true;

  if (sum > sta->cheat_sheet.arc_enter2.max)
    return true;

  // try to recover
  return false;
}

/// semicircle_enter
void action_4_semicircle_enter(struct Status *sta) {
  INFO("ACTION_4_SEMICIRCLE_ENTER");
  speed_cache_recover(sta);
}

void update_4_semicircle_enter(struct Status *sta) {
  if (sta->sensor.follow_gw != ROAD_NO) {
    int delta = pid_compute(&sta->pid.follow_gw, 0, sta->sensor.follow_gw);

    speed_cache_recover(sta);
    sta->wheels[FONT_LEFT].target += delta;
    sta->wheels[FONT_RIGHT].target -= delta;
  }
}

bool condition_4_semicircle_enter(struct Status *sta) {
  // TODO:
  return sta->sensor.follow_ms != ROAD_NO;
}

/// semicircle_match
void action_4_semicircle_match(struct Status *sta) {
  INFO("ACTION_4_SEMICIRCLE_MATCH");
  speed_cache_recover(sta);
}

void update_4_semicircle_match(struct Status *sta) {
  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);

  speed_cache_recover(sta);

  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}

bool condition_4_semicircle_match(struct Status *sta) {
  // TODO:
  return sta->sensor.follow_ms == ROAD_NO;
}

/// arc_continue
void action_arc_continue1(struct Status *sta) {
  INFO("ACTION_4_ARC_CONTINUE1");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
}

void action_arc_continue1_fast(struct Status *sta) {
  INFO("ACTION_4_ARC_CONTINUE1");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
}

bool condition_arc_continue1(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;
  return sum > sta->cheat_sheet.arc_continue1;
}

void action_arc_continue2(struct Status *sta) {
  INFO("ACTION_4_ARC_CONTINUE1");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
}

void action_arc_continue2_fast(struct Status *sta) {
  INFO("ACTION_4_ARC_CONTINUE1");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
}

bool condition_arc_continue2(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;
  return sum > sta->cheat_sheet.arc_continue2;
}

void action_2_semicircle_enter(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_ENTER");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedSlow].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedSlow].right;
}
void update_2_semicircle_enter(struct Status *sta) {
  if (sta->sensor.follow_gw == ROAD_NO)
    return;
  int delta = pid_compute(&sta->pid.follow_gw, 0, sta->sensor.follow_gw);
  sta->wheels[FONT_LEFT].target =
      sta->cheat_sheet.turn_speed[SpeedSlow].left + delta;
  sta->wheels[FONT_RIGHT].target =
      sta->cheat_sheet.turn_speed[SpeedSlow].right - delta;
}
bool condition_2_semicircle_enter(struct Status *sta) {
  // continue 2 times
  static bool last = false;
  bool have_road = sta->sensor.follow_ms != ROAD_NO;

  if (have_road && last)
    return true;

  last = have_road;
  return false;
}

void action_semicircle_enter1(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_ENTER");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
}
void action_semicircle_enter1_fast(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_ENTER_FAST");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
}
void update_semicircle_enter1(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;

  if (sta->sensor.follow_gw == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_gw, 0, sta->sensor.follow_gw);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
void update_semicircle_enter1_fast(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;

  if (sta->sensor.follow_gw == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_gw, 0, sta->sensor.follow_gw);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
void action_semicircle_enter2(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_ENTER");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
}
void action_semicircle_enter2_fast(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_ENTER_FAST");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
}
void update_semicircle_enter2(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;

  if (sta->sensor.follow_gw == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_gw, 0, sta->sensor.follow_gw);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
void update_semicircle_enter2_fast(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;

  if (sta->sensor.follow_gw == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_gw, 0, sta->sensor.follow_gw);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
bool condition_semicircle_enter(struct Status *sta) {
  // continue 2 times
  static bool last = false;
  bool have_road = sta->sensor.follow_ms != ROAD_NO;

  if (have_road && last) {
    last = false;
    return true;
  }

  last = have_road;
  return false;
}

void action_2_semicircle_match(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_MATCH");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
}
void update_2_semicircle_match(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;

  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
bool condition_2_semicircle_match(struct Status *sta) {
  return sta->sensor.follow_ms == ROAD_NO;
}

void action_semicircle_match1(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_MATCH");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
}
void action_semicircle_match1_fast(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_MATCH_FAST");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
}
void update_semicircle_match1(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;

  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
void update_semicircle_match1_fast(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;

  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
void action_semicircle_match2(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_MATCH");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;
}
void action_semicircle_match2_fast(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_MATCH_FAST");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;
}
void update_semicircle_match2(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedNorm].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedNorm].right;

  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
void update_semicircle_match2_fast(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.turn_speed[SpeedFast].left;
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.turn_speed[SpeedFast].right;

  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
  sta->wheels[FONT_LEFT].target += delta;
  sta->wheels[FONT_RIGHT].target -= delta;
}
bool condition_semicircle_match(struct Status *sta) {
  return sta->sensor.follow_ms == ROAD_NO;
}
