#include "keep_angle.h"
#include "User/move/turn.h"
#include "User/utils/pid.h"
#include "turn.h"
#include <stdint.h>

struct Pid keep_angle_pid;
float static_keep_angle = 0.0;

void keep_angle_set(float angle) {
  static_keep_angle = angle;
  pid_init(&keep_angle_pid, 1, 0, 0, 3, 5);
}

void start_keep_angle(float angle) {
  { keep_angle_set(angle); }
}

void keep_angle() {
  float diff;
  diff = turn_head_diff(static_keep_angle, turn_abs_origin);
  int turn_speed = pid_compute(&keep_angle_pid, 0, -diff);
  // printTo(uart3, "%f    %d\r\n", diff, turn_speed);
  if (turn_speed > TURN_SPEED)
    turn_speed = TURN_SPEED;
  if (turn_speed < -TURN_SPEED)
    turn_speed = -TURN_SPEED;
  left_tar += -turn_speed;
  right_tar += turn_speed;
}
