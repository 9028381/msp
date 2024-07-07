#include "motor.h"
#include "../encounter.h"
#include "../utils/math.h"
#include "ti/driverlib/dl_gpio.h"

uint16_t encounter[WHEEL_NUMS];

void encounter_init();
void motor_init() { encounter_init(); }

int motor_get_speed(enum WheelPosition which) {
  int speed = encounter[which] - 0xefff;
  encounter[which] = 0xefff;
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

void encounter_init() {
  for (unsigned int i = 0; i < WHEEL_NUMS; i++)
    encounter[i] = 0xefff;

  NVIC_EnableIRQ(GPIOA_INT_IRQn);
  NVIC_EnableIRQ(GPIOB_INT_IRQn);
}

#define GPIO_READ(port, pin) DL_GPIO_readPins(port, pin) ? 1 : -1

void M1_CH1_INT() {
  encounter[FONT_LEFT] += GPIO_READ(M1_M1_CH2_PORT, M1_M1_CH2_PIN);
}
void M2_CH1_INT() {
  encounter[FONT_RIGHT] += GPIO_READ(M2_M2_CH2_PORT, M2_M2_CH2_PIN);
}
void M3_CH1_INT() {
  encounter[BACK_LEFT] += GPIO_READ(M3_M3_CH2_PORT, M3_M3_CH2_PIN);
}
void M4_CH1_INT() {
  encounter[BACK_RIGHT] += GPIO_READ(M4_PORT, M4_M4_CH1_IIDX);
}
