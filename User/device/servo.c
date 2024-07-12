#include "servo.h"

#define SERVO_MAX_ANGLE 180

#include "ti_msp_dl_config.h"

void servo_set_angle(enum SERVO servo, float angle) {
  if ((int)angle > SERVO_MAX_ANGLE / 2)
    angle = (float)SERVO_MAX_ANGLE / 2;
  if ((int)angle < -SERVO_MAX_ANGLE / 2)
    angle = -(float)SERVO_MAX_ANGLE / 2;
  if (servo == SERVO_A) {
    DL_Timer_setCaptureCompareValue(
        SERVO_INST,
        (int)((angle / ((float)SERVO_MAX_ANGLE / 2)) * 0.05 * 3200 +
              0.075 * 3200),
        DL_TIMER_CC_0_INDEX);
  } else if (servo == SERVO_B) {
    DL_Timer_setCaptureCompareValue(
        SERVO_INST,
        (int)((angle / ((float)SERVO_MAX_ANGLE / 2)) * 0.05 * 3200 +
              0.075 * 3200),
        DL_TIMER_CC_1_INDEX);
  }

  return;
}
