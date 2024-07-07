#include "motor.h"
#include "../encounter.h"
#include "../utils/math.h"
#include "ti/driverlib/dl_gpio.h"

int motor_get_speed(enum WheelPosition which) {
  int speed;
  switch (which) {
  case FONT_LEFT:
    speed = L_1 - 0xefff;
    L_1 = 0xefff;
    break;
  case FONT_RIGHT:
    speed = L_2 - 0xefff;
    L_2 = 0xefff;
    break;
  case BACK_LEFT:
    speed = L_3 - 0xefff;
    L_3 = 0xefff;
    break;
  case BACK_RIGHT:
    speed = L_4 - 0xefff;
    L_4 = 0xefff;
    break;
  }
  return speed;
}

#define MOTOR_DRIVE(fport, fpin, bport, bpin, thrust, pwm_timercc)             \
  {                                                                            \
    if (thrust > 0) {                                                          \
      DL_GPIO_setPins(fport, fpin);                                            \
      DL_GPIO_clearPins(bport, bpin);                                          \
    } else if (thrust < 0) {                                                   \
      DL_GPIO_clearPins(fport, fpin);                                          \
      DL_GPIO_setPins(bport, bpin);                                            \
    } else {                                                                   \
      DL_GPIO_clearPins(fport, fpin);                                          \
      DL_GPIO_clearPins(bport, bpin);                                          \
    }                                                                          \
    DL_Timer_setCaptureCompareValue(M_PWM_INST, ABS(thrust), pwm_timercc);     \
  }

void motor_set_thrust(enum WheelPosition which, int thrust) {
  switch (which) {
  case FONT_LEFT:
    MOTOR_DRIVE(M1_M1_D1_PORT, M1_M1_D1_PIN, M1_M1_D2_PORT, M1_M1_D2_PIN,
                thrust, DL_TIMER_CC_0_INDEX);
    break;
  case FONT_RIGHT:
    MOTOR_DRIVE(M2_M2_D1_PORT, M2_M2_D1_PIN, M2_M2_D2_PORT, M2_M2_D2_PIN,
                thrust, DL_TIMER_CC_1_INDEX);
    break;
  case BACK_LEFT:
    MOTOR_DRIVE(M3_M3_D1_PORT, M3_M3_D1_PIN, M3_M3_D2_PORT, M3_M3_D2_PIN,
                thrust, DL_TIMER_CC_2_INDEX);
    break;
  case BACK_RIGHT:
    MOTOR_DRIVE(M4_PORT, M4_M4_D1_PIN, M4_PORT, M4_M4_D2_PIN, thrust,
                DL_TIMER_CC_3_INDEX);
    break;
  }
}
