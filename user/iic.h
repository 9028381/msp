#ifndef __IIC_H_
#define __IIC_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "empty/ti_msp_dl_config.h"

#define GYR_PORT IIC_GYR_PORT
#define GYR_SDA IIC_GYR_SDA_PIN
#define GYR_SCL IIC_GYR_SCL_PIN

#define IIC_SCL_OUT DL_GPIO_initDigitalOutput(IIC_GYR_SCL_IOMUX)
#define IIC_SCL_IN DL_GPIO_initDigitalInput(IIC_GYR_SCL_IOMUX)
#define IIC_SDA_OUT DL_GPIO_initDigitalOutput(IIC_GYR_SDA_IOMUX)
#define IIC_SDA_IN DL_GPIO_initDigitalInput(IIC_GYR_SDA_IOMUX)

#define IIC_SCL_HIGH DL_GPIO_setPins(GYR_PORT, IIC_GYR_SCL_PIN)
#define IIC_SCL_LOW DL_GPIO_clearPins(GYR_PORT, IIC_GYR_SCL_PIN)

#define IIC_SDA_HIGH DL_GPIO_setPins(GYR_PORT, IIC_GYR_SDA_PIN)
#define IIC_SDA_LOW DL_GPIO_clearPins(GYR_PORT, IIC_GYR_SDA_PIN)

#define IIC_SDA_READ (bool)DL_GPIO_readPins(GYR_PORT, IIC_GYR_SDA_PIN)
#define IIC_SCL_READ (bool)DL_GPIO_readPins(GYR_PORT, IIC_GYR_SCL_PIN)


#endif
