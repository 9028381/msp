#include "LED.h"
#include "ti_msp_dl_config.h"

void LED_set(uint8_t sta)
{
    if(sta == 0)
    {
        DL_GPIO_setPins(LED_PORT_PORT, LED_PORT_LED_PIN);
    }
    else {
        DL_GPIO_clearPins(LED_PORT_PORT, LED_PORT_LED_PIN);
    }
}
