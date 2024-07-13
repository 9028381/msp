#include "status.h"
#include "../device/gw_gray.h"
#include "../device/gyroscope.h"
#include "../utils/pid.h"

struct Status status;

void status_init(struct Status *status) {
  // time init
  status->times = 0;

  // sensor init

  // move pid init
  pid_init(&status->pid.turn, 0, 0, 0, 0, 0);
  pid_init(&status->pid.follow, 0, 0, 0, 0, 0);

  // wheels init
  status->base_speed = 0;
  status_wheels_init(status->wheels);

  // mode init
  status->mode.turn = false;
  status->mode.follow = false;
}

void status_next(struct Status *status) {
  // time next
  status->times++;

  // encoder next
  status_wheels_next_speed(status->wheels);

  // motor base speed
  for (int i = 0; i < WHEEL_NUMS; i++)
    status->wheels[i].target = status->base_speed;

  // sensor next
  if (status->mode.turn)
    status->sensor.gyro = gyr_get_value(gyr_z_yaw);

  if (status->mode.follow)
    status->sensor.follow = gw_gray_get_diff();

  // update wheel target speed based on sensor
  if (status->mode.turn) {
    status->wheels[FONT_LEFT].target += pid_compute(&status->pid.turn, 0, 0);
    status->wheels[FONT_RIGHT].target -= pid_compute(&status->pid.turn, 0, 0);
  }

  if (status->mode.follow) {
    status->wheels[FONT_LEFT].target += pid_compute(&status->pid.follow, 0, 0);
    status->wheels[FONT_RIGHT].target -= pid_compute(&status->pid.follow, 0, 0);
  }

  // update wheel thrust based on wheel target
  status_wheels_next_thrust(status->wheels);

  // wheels drive
  status_wheels_drive(status->wheels);

  // mode next
}
