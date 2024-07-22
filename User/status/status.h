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
  bool record;
  bool repeat;
  bool remote;
};

struct MovePid {
  Pid turn;
  Pid follow;
  Pid remote_forward;
  Pid remote_theta;
};

struct Direction {
  float origin;
  float target;
};

struct RemotePosition {
  int forward;
  int theta;
};

struct Status {
  /// times / STATUS_FREQ == run time(s)
  unsigned times;
  struct Sensor sensor;
  struct MovePid pid;
  struct Direction dir;
  short base_speed;
  struct Wheel wheels[WHEEL_NUMS];
  struct Mode mode;
  struct RemotePosition remote_position;
  unsigned record_or_repeat_reference_time;
};

extern struct Status status;

void status_init(struct Status *status);
void status_next(struct Status *status);

#endif // !__STATUS_H__
