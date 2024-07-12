#include "delay.h"
#include "ti_msp_dl_config.h"

#define CLOCK 32

void delay_us(unsigned int t) { delay_cycles(CLOCK * t); }
