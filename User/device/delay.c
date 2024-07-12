#include "delay.h"
#include "ti/driverlib/m0p/dl_core.h"

void delay_us(uint32_t t)
{
    delay_cycles(CLOCK * t);
}