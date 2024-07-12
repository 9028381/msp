#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "../device/wheel.h"

void motor_init();
int motor_get_speed(enum WheelPosition which);
void motor_set_thrust(enum WheelPosition which, int thrust);

void M1_CH1_INT();
void M2_CH1_INT();
void M3_CH1_INT();
void M4_CH1_INT();

#endif // !__MOTOR_H__
