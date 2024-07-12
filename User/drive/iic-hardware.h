#ifndef IIC_HW_H
#define IIC_HW_H

#include <stdint.h>

void iic_hardware_write(uint8_t DEV_ADDR, uint8_t size, uint8_t *pData);
void iic_handware_read(uint8_t DEV_ADDR, uint8_t size, uint8_t *pData);

#endif
