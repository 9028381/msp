#ifndef __CONTROL_CENTER_H_
#define __CONTROL_CENTER_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "empty/ti_msp_dl_config.h"

extern int32_t M_F_L_cur;
extern int32_t M_F_R_cur;
extern int32_t M_B_L_cur;
extern int32_t M_B_R_cur;

extern int32_t M_F_L_tar;
extern int32_t M_F_R_tar;
extern int32_t M_B_L_tar;
extern int32_t M_B_R_tar;

#endif
