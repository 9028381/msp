#include "wheel.h"
#include "../drive/motor.h"
#include "../utils/log.h"
#include "../utils/math.h"

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
  INFO("motor init.");
  motor_init();

  status_wheel_init(wheels, FONT_LEFT, 2, 1, 0, 5, 50);
  status_wheel_init(wheels, FONT_RIGHT, 2, 1, 0, 5, 50);
  status_wheel_init(wheels, BACK_LEFT, 1, 1, 1, 5, 50);
  status_wheel_init(wheels, BACK_RIGHT, 1, 1, 1, 5, 50);
}

void status_wheel_next_speed(struct Wheel wheels[WHEEL_NUMS],
                             enum WheelPosition which) {
  struct Wheel *wheel = &wheels[which];
  int speed = motor_get_speed(which);
  wheel->current = speed;
  wheel->history += speed;
}

void status_wheels_next_speed(struct Wheel wheels[WHEEL_NUMS]) {
  for (unsigned int which = 0; which < WHEEL_NUMS; which++)
    status_wheel_next_speed(wheels, which);
}

void status_wheel_next_thrust(struct Wheel wheels[WHEEL_NUMS],
                              enum WheelPosition which) {
  struct Wheel *wheel = &wheels[which];
  wheel->thrust += pid_compute(&wheel->pid, wheel->target, wheel->current);
  wheel->thrust = CLAMP(wheel->thrust, WHEEL_THRUST_MAX);
}

void status_wheels_next_thrust(struct Wheel wheels[WHEEL_NUMS]) {
  for (unsigned int which = 0; which < WHEEL_NUMS; which++)
    status_wheel_next_thrust(wheels, which);
}

void status_wheels_drive(struct Wheel wheels[WHEEL_NUMS]) {
  for (unsigned int which = 0; which < WHEEL_NUMS; which++)
    motor_set_thrust(which, wheels[which].thrust);
}
