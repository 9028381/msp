#ifndef __ENCOUNTER_H_
#define __ENCOUNTER_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "empty/ti_msp_dl_config.h"

extern uint32_t L_1;
extern uint32_t L_2;
extern uint32_t L_3;
extern uint32_t L_4;

extern void init_encounter();

extern void M1_CH1_INT();
extern void M2_CH1_INT();
extern void M3_CH1_INT();
extern void M4_CH1_INT();

#endif
