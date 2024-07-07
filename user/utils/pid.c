#include "pid.h"
#include "log.h"
#include "math.h"

void pid_init(Pid *pid, float kp, float ki, float kd,
              unsigned char integral_length, unsigned int integral_max) {
  if (integral_length <= 1) {
    THROW_ERROR("PID_INIT_ERROR: integral_max is less than 2."
                " Not enough space to record the difference."
                " Try to set integral_max = 2 and set ki = 0.");
    integral_length = 2;
    ki = 0.0;
  }

  if (integral_length > PID_DATA_LOOP_LENGTH_MAX) {
    THROW_ERROR(
        "PID_INIT_ERROR: integral_max is more than PID_DATA_LOOP_LENGTH_MAX."
        " Not enough space to record the integral."
        " Try to set integral_length = PID_DATA_LOOP_LENGTH_MAX."
        " (PID_DATA_LOOP_LENGTH_MAX = %d)",
        PID_DATA_LOOP_LENGTH_MAX);
    integral_length = PID_DATA_LOOP_LENGTH_MAX;
  }

  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;
  pid->index = 0;
  pid->len = integral_length;
  pid->sum = 0;
  pid->sum_max = integral_max;
  for (unsigned char i = 0; i < pid->len; i++)
    pid->data[i] = 0;
}

int pid_compute(Pid *pid, int target, int current) {
  int err = target - current;

  pid->sum += err - pid->data[pid->index];
  pid->sum = CLAMP(pid->sum, pid->sum_max);
  pid->data[pid->index] = err;

  float p = err;
  float i = (float)pid->sum / pid->len;
  float d = err - pid->data[pid->index == 0 ? pid->len - 1 : pid->index - 1];

  pid->index += 1;
  pid->index = pid->index == pid->len ? 0 : pid->index;

  return pid->kp * p + pid->ki * i + pid->kd * d;
}
