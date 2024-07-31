#ifndef __ANSWER4_STEP_H__
#define __ANSWER4_STEP_H__

#include "stdbool.h"

struct Status;

// action
void action_4_arc_enter(struct Status *sta);
void action_4_arc_continue(struct Status *sta);

void action_4_forward(struct Status *sta);

void action_4_semicircle_start(struct Status *sta);
void action_4_semicircle_match(struct Status *sta);

// update
void update_4_arc_enter(struct Status *sta);
void update_4_arc_continue(struct Status *sta);

void update_4_forward(struct Status *sta);

void update_4_semicircle_start(struct Status *sta);
void update_4_semicircle_match(struct Status *sta);

// condition
bool condition_4_arc_enter(struct Status *sta);
bool condition_4_arc_continue(struct Status *sta);

bool condition_4_forward(struct Status *sta);

bool condition_4_semicircle_start(struct Status *sta);
bool condition_4_semicircle_match(struct Status *sta);

#endif
