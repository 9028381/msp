#ifndef __TURN_H_
#define __TURN_H_

#include "User/device/wheel.h"
#include "User/task/task.h"
#include "User/task/timed.h"
#include "User/device/gyroscope.h"
#include "User/status/status.h"
#include "User/utils/pid.h"

#define TURN_SPEED_H 700
#define TURN_SPEED_L 300


extern float turn_abs_origin;

extern void turn_abs_start_turn(int16_t angle, uint8_t time);
void turn_abs_head_init(void);
float turn_head_diff(float angle, float origin_angle);


#endif
