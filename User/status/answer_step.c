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
void action_4_semicircle_start(struct Status *sta) {
  INFO("ACTION_4_SEMICIRCLE_START");
  action_4_semicircle_match(sta);
}

void update_4_semicircle_start(struct Status *sta) {
  update_4_semicircle_match(sta);
}

bool condition_4_semicircle_start(struct Status *sta) {
  return condition_4_semicircle_match(sta);
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

void action_1_forward(struct Status *sta) {
  INFO("ACTION_1_FORWARD");
  sta->wheels[FONT_LEFT].target = sta->cheat_sheet.forward_speed[SpeedSlow];
  sta->wheels[FONT_RIGHT].target = sta->cheat_sheet.forward_speed[SpeedSlow];
}

bool condition_1_forward_stop_B_100cm(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  int sum = history.left + history.right;
  // TODO:
  return sum > sta->cheat_sheet.AtoB.min &&
         (sum > sta->cheat_sheet.AtoB.max || sta->sensor.follow_gw != ROAD_NO);
}

/// arc_enter
void action_4_arc_enter(struct Status *sta) {
  INFO("ACTION_4_ARC_ENTER");
  speed_cache_recover(sta);
}

void update_4_arc_enter(struct Status *sta) {}

bool condition_4_arc_enter(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  if (history.left + history.right < 42000)
    return false;

  if (sta->sensor.follow_gw != ROAD_NO)
    return true;

  if (history.left + history.right > 99999)
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
void action_4_arc_continue(struct Status *sta) {
  INFO("ACTION_4_ARC_CONTINUE");
  speed_cache_recover(sta);
}

void update_4_arc_continue(struct Status *sta) {}

bool condition_4_arc_continue(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  return history.left + history.right > 55000;
}

void action_2_semicircle_enter(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_ENTER");
  sta->wheels[FONT_LEFT].target = 200;
  sta->wheels[FONT_RIGHT].target = 144;
}
void update_2_semicircle_enter(struct Status *sta) {
  int delta = pid_compute(&sta->pid.follow_gw, 0, sta->sensor.follow_gw);
  sta->wheels[FONT_LEFT].target = 200 + delta;
  sta->wheels[FONT_RIGHT].target = 144 - delta;
}
bool condition_2_semicircle_enter(struct Status *sta) {
  return sta->sensor.follow_ms != ROAD_NO;
}

void action_2_semicircle_match(struct Status *sta) {
  INFO("ACTION_2_SEMICIRCLE_MATCH");
  sta->wheels[FONT_LEFT].target = 200;
  sta->wheels[FONT_RIGHT].target = 144;
}
void update_2_semicircle_match(struct Status *sta) {
  if (sta->sensor.follow_ms == ROAD_NO)
    return;

  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
  sta->wheels[FONT_LEFT].target = 200 + delta;
  sta->wheels[FONT_RIGHT].target = 144 - delta;
}
bool condition_2_semicircle_match(struct Status *sta) {
  static bool last = false;
  bool no_road = sta->sensor.follow_ms == ROAD_NO;

  if (no_road && last)
    return true;

  last = no_road;
  return false;
}
