#ifndef __SERVO_H_
#define __SERVO_H_

enum SERVO {
  SERVO_A = 1,
  SERVO_B = 2,
};

extern void servo_set_angle(enum SERVO servo, float angle);

#endif
