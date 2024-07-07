#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "../status/wheel.h"

void motor_init();
int motor_get_speed(enum WheelPosition which);
void motor_set_thrust(enum WheelPosition which, int thrust);

#endif // !__MOTOR_H__
