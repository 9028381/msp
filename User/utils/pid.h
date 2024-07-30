#ifndef __PID_H__
#define __PID_H__

#include "../config.h"
#include "stdbool.h"

struct Pid {
  float kp, ki, kd;
  short data[PID_DATA_LOOP_LENGTH_MAX];
  unsigned char index;
  unsigned char len;
  int sum;
  int i_max;
  bool is_first;
};
typedef struct Pid Pid;

/// Initialize PID controller
///
/// pid : PID controller to be initialized
/// kp  : Proportional gain of the PID controller
/// ki  : Integral gain of the PID controller
/// kd  : Derivative gain of the PID controller
/// integral_length : Length of the integral.
/// integral_max    : max of the integral.
///
/// # Notice
///
/// - The PID controller must be initialized before use.
/// - 2 <= integral_length <= PID_DATA_LOOP_LENGTH_MAX
///   PID_DATA_LOOP_LENGTH_MAX see in config.h
///
/// # Example
///
/// ```c
/// #include "pid.h"
///
/// int main () {
///   Pid pid;
///   pid_init(&pid, 0.5, 0.5, 0.5, PID_DATA_LOOP_LENGTH_MAX);
///   // do something
///   while (true){
///     int target = get_target();
///     int current = get_current();
///     int target = pid_compute(&pid, target, current);
///     // do something
///   }
/// }
///```
void pid_init(Pid *pid, float kp, float ki, float kd,
              unsigned char integral_length, unsigned int integral_max);

/// Computes the PID control value.
///
/// pid     : The initialized PID controller.
/// target  : The desired target value.
/// current : The current value.
/// return  : The computed PID control value.
///
/// This function computes the PID control value based on the difference between
/// the target value and the current value. It updates the error sum and the
/// error history in the PID controller. The PID control value is calculated
/// using the proportional, integral, and derivative terms based on the error,
/// the error sum, and the difference between the current error and the previous
/// error.
///
/// # Notice
/// - The PID controller must be initialized before calling this function.
/// - ABS(target - current) must be less than short::MAX
///
/// # Example
/// ```c
/// #include "pid.h"
/// int main () {
///   Pid pid;
///   pid_init(&pid, 0.5, 0.5, 0.5, PID_DATA_LOOP_LENGTH_MAX);
///   // Additional operations
///   while (true){
///     int target = get_target();
///     int current = get_current();
///     int value = pid_compute(&pid, target, current);
///     // Use the computed PID control value
///     // Additional operations
///   }
/// }
///```
///
int pid_compute(Pid *pid, int target, int current);

#endif // !__PID_H__
