#ifndef __STATUS_H__
#define __STATUS_H__

#include "../config.h"
#include "wheel.h"

struct Sensor {};

enum Mode { FOWARD };

struct Status {
  /// times / STATUS_FREQ == run time(s)
  unsigned int times;
  struct Sensor sensor;
  struct Wheel wheels[WHEEL_NUMS];
  enum Mode mode;
};

extern struct Status status;

void status_init(struct Status *status);
void status_next(struct Status *status);

#endif // !__STATUS_H__
