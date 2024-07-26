#ifndef __STATUS_H__
#define __STATUS_H__

#include "../config.h"
#include "../device/wheel.h"
#include "stdbool.h"
#include "step.h"

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
  Pid history[WHEEL_NUMS];
};

struct Direction {
  float origin;
  float target;
};

struct RemotePosition {
  int forward;
  int theta;
};

struct SnapShot {
  unsigned times;
  int wheels_history[WHEEL_NUMS];
  unsigned duration;
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
  struct SnapShot rec;
  struct Step step;
};

extern struct Status status;

void status_init(struct Status *status);
void status_next(struct Status *status);

#endif // !__STATUS_H__
