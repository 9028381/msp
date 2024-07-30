#include "answer4_step.h"
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
struct SpeedCache speed_cache = {.left = 520, .right = 386};
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

/// arc_start
void action_4_arc_start(struct Status *sta) {
  INFO("ACTION_4_ARC_START");
  speed_cache_recover(sta);
}

void update_4_arc_start(struct Status *sta) {}

bool condition_4_arc_start(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  return history.left + history.right > 42000;
}

/// forward
void action_4_forward(struct Status *sta) {
  INFO("ACTION_4_FORWARD");
  speed_cache_rev();
  sta->wheels[FONT_LEFT].target = 520;
  sta->wheels[FONT_RIGHT].target = 520;
}

void update_4_forward(struct Status *sta) {}

bool condition_4_forward(struct Status *sta) {
  struct DurationHistory history = duration_history_get(sta);
  return history.left + history.right > 80000;
}

/// arc_enter
void action_4_arc_enter(struct Status *sta) {
  INFO("ACTION_4_ARC_ENTER");
  speed_cache_recover(sta);
}

void update_4_arc_enter(struct Status *sta) {}

bool condition_4_arc_enter(struct Status *sta) {
  if (sta->sensor.follow_gw != ROAD_NO)
    return true;

  struct DurationHistory history = duration_history_get(sta);
  if (history.left + history.right < 42000)
    return false;

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
  return sta->sensor.follow_gw == ROAD_NO;
}

/// semicircle_match
void action_4_semicircle_match(struct Status *sta) {
  INFO("ACTION_4_SEMICIRCLE_MATCH");
}

void update_4_semicircle_match(struct Status *sta) {
  int delta = pid_compute(&sta->pid.follow_ms, 0, sta->sensor.follow_ms);
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
