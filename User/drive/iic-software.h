#ifndef __GYR_IIC_H_
#define __GYR_IIC_H_

#include "stdint.h"

uint8_t iic_software_read_to_mem(uint8_t addr, uint8_t reg, uint8_t len,
                                 uint8_t *buf);

uint8_t iic_software_write(uint8_t addr, uint8_t len, uint8_t *buf);

#endif
