#ifndef __FOLLOW_LINE_H_
#define __FOLLOW_LINE_H_

#include "User/utils/pid.h"
#include "stdint.h"
#include "User/device/gw_gray.h"
#include "User/status/status.h"
#include "User/device/wheel.h"
#include "User/task/task.h"
#include "User/task/timed.h"
#include "User/device/ms_gray.h"

extern uint8_t gw_bit_weight[8];


enum GET_DIFF_WAYS 
{
    CAM,
    GW_8,
    MS_3,
};


void start_follow_line(uint8_t time);

#endif
