#include "turn.h"
#include "User/utils/log.h"
#include "User/utils/pid.h"
#include <stdint.h>

int8_t turn_abs_cnt = 0;
float turn_abs_angle = 0;
int8_t turn_abs_max_speed = 5;

struct PID *turn_abs_pid;
float turn_abs_origin;
float turn_abs_move_line_angle;
struct Pid turn_pid;

// 初始化转向 得到原始角度 设置pid的值
void turn_abs_head_init(void) {
  turn_abs_origin = gyr_get_value(gyr_z_yaw) + 180;
  pid_init(&turn_pid, 2, 0, 0, 3, 10);
}

float turn_head_abs(float num) { return num >= 0 ? num : -num; }

float turn_head_diff(float angle, float origin_angle) {
  float current = gyr_get_value(gyr_z_yaw) + 180;
  float target = origin_angle + angle;
  target = target > 360 ? target - 360 : target;
  target = target < 0 ? target + 360 : target;
  float tc = target - current;
  if (turn_head_abs(tc) <= 180)
    return tc;
  else {
    if (tc > 180)
      return tc - 360;
    else
      return tc + 360;
  };
}

void turn_abs(void *para) {
  float diff;

  diff = turn_head_diff(turn_abs_angle, turn_abs_origin);
  TRACE(diff, "%f");
  int turn_speed = pid_compute(&turn_pid, 0, -diff);
  if ((diff <= 2) && (diff >= -2)) {
    turn_abs_cnt--;
    if (turn_abs_cnt == 0) {
      turn_abs_angle = 0;
      status.wheels[FONT_LEFT].target = 0;
      status.wheels[FONT_RIGHT].target = 0;

      return;
    }
  }
  if (turn_speed > 100)
    turn_speed = TURN_SPEED;
  if (turn_speed < -100)
    turn_speed = -TURN_SPEED;
  status.wheels[FONT_LEFT].target = -turn_speed;
  status.wheels[FONT_RIGHT].target = turn_speed;

  Task T = task_new(turn_abs, para);
  task_timed_insert(&task.timed, T, (uint32_t)para & 0xff);
}

void turn_abs_start_turn(int16_t angle, uint8_t time) {
  uint32_t para = angle << 16 | time;
  turn_abs_angle = (float)angle;
  turn_abs_cnt = 1;

  Task T = task_new(turn_abs, (void *)para);
  task_timed_insert(&task.timed, T, (uint32_t)para & 0xff);
}
