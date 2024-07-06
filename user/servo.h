#ifndef __SERVO_H_
#define __SERVO_H_

#define SERVO_MAX_ANGLE 180

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "empty/ti_msp_dl_config.h"

enum SERVO {
  SERVO_A = 1,
  SERVO_B = 2,
};

extern void servo_set_angle(enum SERVO servo, float angle);

#endif
