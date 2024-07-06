#ifndef __WHEEL_H__
#define __WHEEL_H__

#include "../utils/pid.h"

#define WHEEL_NUMS 4

enum WheelPosition {
  FONT_LEFT = 0,
  FONT_RIGHT = 1,
  BACK_LEFT = 2,
  BACK_RIGHT = 3,
};

struct Wheel {
  int thrust;
  int target;
  int current;
  int history;
  Pid pid;
};

void status_wheels_init(struct Wheel wheels[WHEEL_NUMS]);

void status_wheels_next(struct Wheel wheels[WHEEL_NUMS]);

#endif // !__WHEEL_H__
