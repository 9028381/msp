#ifndef __CAM_H_
#define __CAM_H_

#include "stdint.h"
#include "stdlib.h"
#include "User/status/status.h"

#define Left_road -20000
#define Right_road 20000
#define T_L_road -25000
#define T_R_road 25000
#define T_B_road 30000
#define CROSS_road -30000

void update_cam_diff(uint8_t buf);
int16_t get_cam_diff(void);

#endif
