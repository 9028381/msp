#include "wheel.h"
#include "../device/motor.h"
#include "../utils/log.h"

#define CASE_RETURN(x)                                                         \
  case x:                                                                      \
    return #x;

char *wheel_position_enum_to_str(enum WheelPosition which) {
  switch (which) {
    CASE_RETURN(FONT_LEFT)
    CASE_RETURN(FONT_RIGHT)
    CASE_RETURN(BACK_LEFT)
    CASE_RETURN(BACK_RIGHT)
  }
}

void status_wheel_init(struct Wheel wheels[WHEEL_NUMS],
                       enum WheelPosition which, float kp, float ki, float kd,
                       unsigned char integral_length,
                       unsigned int integral_max) {
  INFO("wheel %s init.", wheel_position_enum_to_str(which));
  struct Wheel *wheel = &wheels[which];
  pid_init(&wheel->pid, kp, ki, kd, integral_length, integral_max);
  wheel->target = 0;
  wheel->thrust = 0;
  wheel->current = 0;
  wheel->history = 0;
}

void status_wheels_init(struct Wheel wheels[WHEEL_NUMS]) {
  status_wheel_init(wheels, FONT_LEFT, 1, 1, 1, 5, 50);
  status_wheel_init(wheels, FONT_RIGHT, 1, 1, 1, 5, 50);
  status_wheel_init(wheels, BACK_LEFT, 1, 1, 1, 5, 50);
  status_wheel_init(wheels, BACK_RIGHT, 1, 1, 1, 5, 50);
}

void status_wheel_next(struct Wheel wheels[WHEEL_NUMS],
                       enum WheelPosition which) {
  struct Wheel *wheel = &wheels[which];
  int speed = motor_get_speed(which);
  wheel->current = speed;
  wheel->history += speed;
}

void status_wheels_next(struct Wheel wheels[WHEEL_NUMS]) {
  status_wheel_next(wheels, FONT_LEFT);
  status_wheel_next(wheels, FONT_RIGHT);
  status_wheel_next(wheels, BACK_LEFT);
  status_wheel_next(wheels, BACK_RIGHT);
}
