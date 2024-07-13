#include "status.h"
#include "../device/gw_gray.h"
#include "../device/gyroscope.h"

struct Status status;

void status_init(struct Status *status) {
  // time init
  status->times = 0;

  // sensor init

  // wheels init
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

  // sensor next
  if (status->mode.turn)
    status->sensor.gyro = gyr_get_value(gyr_z_yaw);

  if (status->mode.follow)
    status->sensor.follow = gw_gray_get_diff();

  // update wheel target speed based on sensor

  // update wheel thrust based on wheel target
  status_wheels_next_thrust(status->wheels);

  // wheels drive
  status_wheels_drive(status->wheels);

  // mode next
}
