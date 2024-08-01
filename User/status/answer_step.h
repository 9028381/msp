#ifndef __ANSWER4_STEP_H__
#define __ANSWER4_STEP_H__

#include "stdbool.h"

struct Status;

void action_forward_slow(struct Status *sta);
void action_forward_normal(struct Status *sta);
void action_forward_fast(struct Status *sta);
bool condition_forward_stop_B_100cm(struct Status *sta);
bool condition_forward1_limit(struct Status *sta);
bool condition_forward2_limit(struct Status *sta);

void action_arc_start(struct Status *sta);
bool condition_arc_start(struct Status *sta);

void action_semicircle_start(struct Status *sta);
void update_semicircle_start(struct Status *sta);
bool condition_semicircle_start(struct Status *sta);

void action_arc_enter1(struct Status *sta);
void action_arc_enter1_fast(struct Status *sta);
bool condition_arc_enter1(struct Status *sta);
void action_arc_enter2(struct Status *sta);
void action_arc_enter2_fast(struct Status *sta);
bool condition_arc_enter2(struct Status *sta);

void action_arc_continue1(struct Status *sta);
void action_arc_continue2(struct Status *sta);
void action_arc_continue1_fast(struct Status *sta);
void action_arc_continue2_fast(struct Status *sta);
bool condition_arc_continue1(struct Status *sta);
bool condition_arc_continue2(struct Status *sta);

void action_semicircle_enter1(struct Status *sta);
void update_semicircle_enter1(struct Status *sta);
void action_semicircle_enter2(struct Status *sta);
void update_semicircle_enter2(struct Status *sta);
void action_semicircle_enter1_fast(struct Status *sta);
void update_semicircle_enter1_fast(struct Status *sta);
void action_semicircle_enter2_fast(struct Status *sta);
void update_semicircle_enter2_fast(struct Status *sta);
bool condition_semicircle_enter(struct Status *sta);

void action_semicircle_match1(struct Status *sta);
void update_semicircle_match1(struct Status *sta);
void action_semicircle_match2(struct Status *sta);
void update_semicircle_match2(struct Status *sta);
void action_semicircle_match1_fast(struct Status *sta);
void update_semicircle_match1_fast(struct Status *sta);
void action_semicircle_match2_fast(struct Status *sta);
void update_semicircle_match2_fast(struct Status *sta);
bool condition_semicircle_match(struct Status *sta);

void action_2_semicircle_enter(struct Status *sta);
void update_2_semicircle_enter(struct Status *sta);
bool condition_2_semicircle_enter(struct Status *sta);

void action_2_semicircle_match(struct Status *sta);
void update_2_semicircle_match(struct Status *sta);
bool condition_2_semicircle_match(struct Status *sta);

// action
void action_4_forward(struct Status *sta);

void action_4_semicircle_enter(struct Status *sta);
void action_4_semicircle_match(struct Status *sta);

// update

void update_4_forward(struct Status *sta);

void update_4_semicircle_enter(struct Status *sta);
void update_4_semicircle_match(struct Status *sta);

// condition

bool condition_4_forward(struct Status *sta);

bool condition_4_semicircle_enter(struct Status *sta);
bool condition_4_semicircle_match(struct Status *sta);

#endif
