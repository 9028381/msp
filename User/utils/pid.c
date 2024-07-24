#include "pid.h"
#include "log.h"
#include "math.h"
#include "stdlib.h"

void pid_init(Pid *pid, float kp, float ki, float kd,
              unsigned char integral_length, unsigned int integral_max) {
  if (pid == NULL) {
    THROW_ERROR("PID_INIT_ERROR: pid points to NULL.");
    return;
  }

  if (integral_length <= 1) {
    THROW_WARN("PID_INIT_ERROR: integral_length is less than 2."
               " Not enough space to record the difference."
               " Try to set integral_length = 2 and set ki = 0.0.");
    integral_length = 2;
    ki = 0.0;
  }

  if (integral_length > PID_DATA_LOOP_LENGTH_MAX) {
    THROW_WARN(
        "PID_INIT_ERROR: integral_length is more than PID_DATA_LOOP_LENGTH_MAX."
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
  pid->sum = 0;
  pid->len = integral_length;
  pid->i_max = integral_max;
  for (unsigned char i = 0; i < pid->len; i++)
    pid->data[i] = 0;
}

int pid_compute(Pid *pid, int target, int current) {
  short err = target - current;

  /*
   * pid input: ... -> 0 1 2 3 4 5 6 7 8 9 ...
   *                                     ^
   *                                 inputing
   * pid len = 9
   * pid data =  7 | 8 | 0 | 1 | 2 | 3 | 4 | 5 | 6
   *                     ^
   *                   index
   * 9 will overwrite 0 and index++
   * 0 is the farthest error
   * 8 is the last error
   * 9 is the now error
   * so sum = sum + 9 - 0
   * last error is 8 (data[index-1])
   */
  pid->sum += err - pid->data[pid->index];
  pid->data[pid->index] = err;

  float p = err;
  float i = (float)CLAMP(pid->sum, pid->i_max) / pid->len;
  float d = err - pid->data[pid->index == 0 ? pid->len - 1 : pid->index - 1];

  pid->index += 1;
  pid->index = pid->index == pid->len ? 0 : pid->index;

  return pid->kp * p + pid->ki * i + pid->kd * d;
}
