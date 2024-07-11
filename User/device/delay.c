#include "delay.h"
#include "ti/driverlib/m0p/dl_core.h"

void delay_us(uint32_t t)
{
    uint32_t cnt = CLOCK * t;
    delay_cycles(cnt);
}