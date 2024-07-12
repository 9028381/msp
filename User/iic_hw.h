#ifndef IIC_HW_H
#define IIC_HW_H

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti_msp_dl_config.h"

#include <stdint.h>

void IIC_Write_HW(uint8_t DEV_ADDR, uint8_t size, uint8_t* pData);
void IIC_Read_HW(uint8_t DEV_ADDR, uint8_t size, uint8_t* pData);




#endif
