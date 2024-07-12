#ifndef __TURN_H_
#define __TURN_H_

#include "User/utils/pid_for_turn.h"
#include "User/status/wheel.h"
#include "User/task/task.h"
#include "User/task/timed.h"
#include "User/device/gyroscope.h"
#include "User/status/status.h"

#define TURN_SPEED 500


extern float turn_abs_origin;

extern void turn_abs();
extern void turn_abs_head_init();
extern void turn_abs_start_turn(int16_t angle, uint8_t time);


#endif
