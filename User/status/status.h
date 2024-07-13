#ifndef __STATUS_H__
#define __STATUS_H__

#include "../config.h"
#include "../device/wheel.h"
#include "stdbool.h"

struct Sensor {
  /// [-180, 180]
  float gyro;
  /// [-1000, 1000]
  short follow;
};

struct Mode {
  bool turn;
  bool follow;
};

struct Status {
  /// times / STATUS_FREQ == run time(s)
  unsigned int times;
  struct Sensor sensor;
  struct Wheel wheels[WHEEL_NUMS];
  struct Mode mode;
};

extern struct Status status;

void status_init(struct Status *status);
void status_next(struct Status *status);

#endif // !__STATUS_H__
