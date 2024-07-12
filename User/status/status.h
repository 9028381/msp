#ifndef __STATUS_H__
#define __STATUS_H__

#include "../config.h"
#include "wheel.h"

struct Sensor {};

enum Mode { 
    STOP,
    FOWARD,
    BACKWARD,
    FOLLOW_LINE,
    TURN_RIGHT,
    TURN_LEFT,
    };

struct Status {
  /// times / STATUS_FREQ == run time(s)
  uint32_t times;
  struct Sensor sensor;
  struct Wheel wheels[WHEEL_NUMS];
  enum Mode mode;
};

extern struct Status status;

void status_init(struct Status *status);
void status_next(struct Status *status);
void status_drive(struct Status *status);

#endif // !__STATUS_H__
