#include "status.h"
#include "../device/cam.h"
#include "../device/flash.h"
#include "../device/gw_gray.h"
#include "../device/gyroscope.h"
#include "../utils/utils.h"
#include "User/device/wheel.h"
#include "User/utils/log.h"
#include "User/utils/pid.h"
#include "record.h"

struct Status status;

void status_init(struct Status *sta) {
  // time init
  sta->times = 0;

  // sensor init
  // sta->dir.origin = gyr_get_value(gyr_z_yaw);
  sta->dir.target = 0.0;

  // move pid init
  pid_init(&sta->pid.turn, 1, 0, 0.8, 5, 10);
  pid_init(&sta->pid.follow, 1, 0, 0.5, 3, 10); // gw
  // pid_init(&sta->pid.follow, 0.8, 0, 1.8, 3, 10); // cam

  // repeat history pid
  for (int i = 0; i < WHEEL_NUMS; i++)
    pid_init(&sta->pid.history[i], 0.1, 0, 0, 3, 10);

  // remote pid init
  pid_init(&sta->pid.remote_forward, 1, 0, 0, 3, 10); // real remote
  pid_init(&sta->pid.remote_theta, 1, 0, 0, 3, 10);   // real remote
  //   pid_init(&sta->pid.remote_forward, 6, 0, 2.5, 3, 10);  //cam
  //   pid_init(&sta->pid.remote_theta, 2, 0, 1, 3, 10);   //cam

  // wheels init
  sta->base_speed = 0;
  status_wheels_init(sta->wheels);

  // remote position
  sta->remote_position.forward = 0;
  sta->remote_position.theta = 0;

  // mode init
  sta->mode.turn = false;
  sta->mode.follow = false;
  sta->mode.record = false;
  sta->mode.repeat = false;
  sta->mode.remote = false;

  sta->rec_start.times = 0;
  for (int i = 0; i < WHEEL_NUMS; i++)
    sta->rec_start.wheels_history[i] = 0;
}

void status_next(struct Status *sta) {
  // time next
  sta->times++;

  // encoder next
  status_wheels_next_speed(sta->wheels);

  // record
  if (sta->mode.record) {
    status_record(sta->wheels[FONT_LEFT].history -
                  sta->rec_start.wheels_history[FONT_LEFT]);
    status_record(sta->wheels[FONT_RIGHT].history -
                  sta->rec_start.wheels_history[FONT_RIGHT]);
  }

  // remote
  if (sta->mode.remote) {
    int forward =
        pid_compute(&sta->pid.remote_forward, sta->remote_position.forward, 0);
    int theta =
        pid_compute(&sta->pid.remote_theta, sta->remote_position.theta, 0);

    sta->wheels[FONT_LEFT].target = forward + theta;
    sta->wheels[FONT_RIGHT].target = forward - theta;

    // PRINTLN("f:%d,
    // t:%d",sta->remote_position.forward,sta->remote_position.theta);
    // PRINTLN("L: %d, R: %d",forward + theta, forward - theta);

    goto THRUST_MOTOR;
  }

  // motor base speed
  for (int i = 0; i < WHEEL_NUMS; i++)
    sta->wheels[i].target = sta->base_speed;

  // sensor next
  if (sta->mode.turn)
    sta->sensor.gyro = gyr_get_value(gyr_z_yaw);

  if (sta->mode.follow)
    // sta->sensor.follow = get_cam_diff();
    sta->sensor.follow = gw_gray_get_diff();

  // update wheel target speed based on sensor
  if (sta->mode.turn) {
    float diff = sta->dir.target + sta->dir.origin - sta->sensor.gyro;
    diff = WARPPING(diff, -180.0, 180.0);
    // PRINTLN("origin:%f, tar:%f, diff:%f", sta->dir.origin,
    // sta->dir.target,diff);
    int delta = pid_compute(&sta->pid.turn, 0, diff * 10);
    delta = CLAMP(delta, MAX_TURN_SPEED); // LIMIT MAX TURN SPEED
    sta->wheels[FONT_LEFT].target += delta;
    sta->wheels[FONT_RIGHT].target -= delta;
  }

  if (sta->mode.follow) {
    int delta;
    switch (sta->sensor.follow) {
    case ROAD_LEFT:
      sta->wheels[FONT_LEFT].target = -MAX_FOLLOW_TURN_SPEED;
      sta->wheels[FONT_RIGHT].target = MAX_FOLLOW_TURN_SPEED;
      break;
    case ROAD_RIGHT:
      sta->wheels[FONT_LEFT].target = MAX_FOLLOW_TURN_SPEED;
      sta->wheels[FONT_RIGHT].target = -MAX_FOLLOW_TURN_SPEED;
      break;
    case ROAD_CROSS:
      sta->wheels[FONT_LEFT].target = 0;
      sta->wheels[FONT_RIGHT].target = 0;
      sta->wheels[FONT_LEFT].target = -MAX_FOLLOW_TURN_SPEED;
      sta->wheels[FONT_RIGHT].target = MAX_FOLLOW_TURN_SPEED;
      break;
    case ROAD_TB:
      sta->wheels[FONT_LEFT].target = 0;
      sta->wheels[FONT_RIGHT].target = 0;
      break;
    case ROAD_TR:
    case ROAD_TL:
      break;
    default:
      delta = pid_compute(&sta->pid.follow, 0, sta->sensor.follow);
      sta->wheels[FONT_LEFT].target += delta;
      sta->wheels[FONT_RIGHT].target -= delta;
      break;
    }
  }

THRUST_MOTOR:
  if (sta->mode.repeat) {
    const int *rec = flash_use(0);
    const int *tar = rec + (sta->times - sta->rec_start.times) * 2;
    sta->wheels[FONT_LEFT].target =
        pid_compute(&sta->pid.history[FONT_LEFT], tar[0],
                    sta->wheels[FONT_LEFT].history -
                     sta->rec_start.wheels_history[FONT_LEFT]);
    sta->wheels[FONT_RIGHT].target =
        pid_compute(&sta->pid.history[FONT_RIGHT], tar[1],
                    sta->wheels[FONT_RIGHT].history -
                        sta->rec_start.wheels_history[FONT_RIGHT]);
  }

  // update wheel thrust based on wheel target
  status_wheels_next_thrust(sta->wheels);

  // if (sta->mode.record) {
  //   sta->wheels[FONT_LEFT].thrust = 1;
  //   sta->wheels[FONT_RIGHT].thrust = 1;
  // }

  // wheels drive
  status_wheels_drive(sta->wheels);

  // mode next
}
