#include "pid.h"
#include "math.h"

void pid_init(Pid *pid, float kp, float ki, float kd,
              unsigned char integral_length) {
  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;
  pid->index = 0;
  pid->len = integral_length;
  pid->sum = 0;
  for (unsigned char i = 0; i < pid->len; i++)
    pid->data[i] = 0;
}

int pid_compute(Pid *pid, int target, int current) {
  int err = target - current;

  pid->sum += err - pid->data[pid->index];
  pid->data[pid->index] = err;

  float p = err;
  float i = (float)CLAMP(pid->sum, PID_I_MAX_LIMIT) / pid->len;
  float d = err - pid->data[pid->index == 0 ? pid->len - 1 : pid->index - 1];

  pid->index += 1;
  pid->index = pid->index == pid->len ? 0 : pid->index;

  return pid->kp * p + pid->ki * i + pid->kd * d;
}
