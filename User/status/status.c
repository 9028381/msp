#include "status.h"
#include "../device/gw_gray.h"
#include "../device/gyroscope.h"
#include "../utils/utils.h"

struct Status status;

void status_init(struct Status *status) {
  // time init
  status->times = 0;

  // sensor init
  status->dir.origin = gyr_get_value(gyr_z_yaw);
  status->dir.target = 0.0;

  // move pid init
  pid_init(&status->pid.turn, 2, 0, 1, 5, 10);
  pid_init(&status->pid.follow, 1, 0, 0, 3, 10);

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
    float diff = status->dir.target + status->dir.origin - status->sensor.gyro;
    diff = WARPPING(diff, -180.0, 180.0);
    int delta = pid_compute(&status->pid.turn, 0, diff * 10);
    delta = CLAMP(delta, MAX_TURN_SPEED); // LIMIT MAX TURN SPEED
    status->wheels[FONT_LEFT].target += delta;
    status->wheels[FONT_RIGHT].target -= delta;
  }

  if (status->mode.follow) {
    int delta = pid_compute(&status->pid.follow, 0, status->sensor.follow);
    // delta = CLAMP(delta, MAX_FOLLOW_TURN_SPEED);
    status->wheels[FONT_LEFT].target += delta;
    status->wheels[FONT_RIGHT].target -= delta;
    status->wheels[FONT_LEFT].target = CLAMP(status->wheels[FONT_LEFT].target, MAX_FOLLOW_TURN_SPEED);
    status->wheels[FONT_RIGHT].target = CLAMP(status->wheels[FONT_RIGHT].target ,  MAX_FOLLOW_TURN_SPEED);
  }

  // update wheel thrust based on wheel target
  status_wheels_next_thrust(status->wheels);

  // wheels drive
  status_wheels_drive(status->wheels);

  // mode next
}
