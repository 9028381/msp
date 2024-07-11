#ifndef __PID_H__
#define __PID_H__

#include "../config.h"

struct Pid {
  float kp, ki, kd;
  int data[PID_DATA_LOOP_LENGTH_MAX];
  unsigned char index;
  unsigned char len;
  int sum;
  int i_max;
};
typedef struct Pid Pid;

/**
 * @brief Initialize PID controller
 * @param pid PID controller to be initialized
 * @param kp Proportional gain of the PID controller
 * @param ki Integral gain of the PID controller
 * @param kd Derivative gain of the PID controller
 * @param integral_length Length of the integral.
 * @param integral_max max of the integral.
 * must in range[2, PID_DATA_LOOP_LENGTH_MAX], see <config.h>.
 *
 * @notice:
 * - The PID controller must be initialized before use.
 * - 2 <= integral_length <= PID_DATA_LOOP_LENGTH_MAX
 *
 * @example:
 * ```c
 * #include "pid.h"
 * Pid pid;
 * int main () {
 *   pid_init(&pid, 0.5, 0.5, 0.5, PID_DATA_LOOP_LENGTH_MAX);
 *   // do something
 *   while (true){
 *     target = get_target();
 *     current = get_current();
 *     value = pid_compute(&pid, target, current);
 *     // do something
 *   }
 * }
 * ```
 */
void pid_init(Pid *pid, float kp, float ki, float kd,
              unsigned char integral_length, unsigned int integral_max);

/**
 * @brief Computes the PID control value.
 * @param pid The initialized PID controller.
 * @param target The desired target value.
 * @param current The current value.
 * @return The computed PID control value.
 *
 * This function computes the PID control value based on the difference between
 * the target value and the current value. It updates the error sum and the
 * error history in the PID controller. The PID control value is calculated
 * using the proportional, integral, and derivative terms based on the error,
 * the error sum, and the difference between the current error and the previous
 * error.
 *
 * @note
 * - The PID controller must be initialized before calling this function.
 * - The computed PID control value can be used to adjust the system to minimize
 * the difference between the target value and the current value.
 *
 * @example
 * ```c
 * #include "pid.h"
 * Pid pid;
 * int main () {
 *   pid_init(&pid, 0.5, 0.5, 0.5, PID_DATA_LOOP_LENGTH_MAX);
 *   // Additional operations
 *   while (true){
 *     target = get_target();
 *     current = get_current();
 *     int value = pid_compute(&pid, target, current);
 *     // Use the computed PID control value
 *     // Additional operations
 *   }
 * }
 * ```
 */
int pid_compute(Pid *pid, int target, int current);

#endif // !__PID_H__
