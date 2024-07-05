#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "C:/ti/mspm0_sdk_2_01_00_03/examples/nortos/LP_MSPM0G3507/driverlib/empty/ti_msp_dl_config.h"

enum MOTOR {
  M_F_L = 1,
  M_F_R = 2,
  M_B_L = 3,
  M_B_R = 4,
};

extern int32_t get_speed(enum MOTOR M);
extern void set_speed(enum MOTOR M, int32_t speed);
extern void pid_keep_speed();
extern void init_PID();

#endif
