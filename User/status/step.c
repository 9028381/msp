#include "step.h"
#include "../utils/utils.h"
#include "status.h"

void step_init(struct Step *step) {
  step->no = 0;
  step->len = 0;
}
void step_push(struct Step *step, step_fn fn) {
  if (step->len > STATUS_STEP_LIMIT) {
    THROW_WARN("STEP_PUSH_OVERFLOW len is %d, but STATUS_STEP_LIMIT is %d. "
               "Will ignore.",
               step->len, STATUS_STEP_LIMIT);
    return;
  }

  step->fn[step->len] = fn;
  step->len += 1;
};

void step_next(struct Step *step, struct Status *sta) {
  if (step->no >= step->len) {
    THROW_WARN("STEP_NEXT_OVERFLOW len is %d, Will stop", step->len);
    step_stop(sta);
    return;
  }

  step->fn[step->no](sta);
  step->no += 1;
}

void step_turn_left(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = -MAX_FOLLOW_TURN_SPEED;
  sta->wheels[FONT_RIGHT].target = MAX_FOLLOW_TURN_SPEED;
}

void step_turn_right(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = MAX_FOLLOW_TURN_SPEED;
  sta->wheels[FONT_RIGHT].target = -MAX_FOLLOW_TURN_SPEED;
}

void step_stop(struct Status *sta) {
  sta->wheels[FONT_LEFT].target = 0;
  sta->wheels[FONT_RIGHT].target = 0;
}

void step_forward(struct Status *sta) {}
