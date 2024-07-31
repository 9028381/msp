#include "iic-software.h"

// headfile move to there

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"


uint8_t iic_software_read_to_mem(uint8_t addr, uint8_t reg, uint8_t len,
                                 uint8_t *buf) {
}

uint8_t iic_software_write(uint8_t addr, uint8_t len, uint8_t *buf) {
}
