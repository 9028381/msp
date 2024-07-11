#ifndef __GYR_IIC_H_
#define __GYR_IIC_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"

#define GYR_PORT IIC_GYR_PORT
#define GYR_SDA IIC_GYR_SDA_PIN
#define GYR_SCL IIC_GYR_SCL_PIN

#define GYR_IIC_SCL_OUT DL_GPIO_initDigitalOutput(IIC_GYR_SCL_GYR_IOMUX)
#define GYR_IIC_SCL_IN DL_GPIO_initDigitalInput(IIC_GYR_SCL_GYR_IOMUX)
#define GYR_IIC_SDA_OUT DL_GPIO_initDigitalOutput(IIC_GYR_SDA_GYR_IOMUX)
#define GYR_IIC_SDA_IN DL_GPIO_initDigitalInput(IIC_GYR_SDA_GYR_IOMUX)

#define GYR_IIC_SCL_HIGH DL_GPIO_setPins(GYR_PORT, IIC_GYR_SCL_GYR_PIN)
#define GYR_IIC_SCL_LOW DL_GPIO_clearPins(GYR_PORT, IIC_GYR_SCL_GYR_PIN)

#define GYR_IIC_SDA_HIGH DL_GPIO_setPins(GYR_PORT, IIC_GYR_SDA_GYR_PIN)
#define GYR_IIC_SDA_LOW DL_GPIO_clearPins(GYR_PORT, IIC_GYR_SDA_GYR_PIN)

#define GYR_IIC_SDA_READ (bool)DL_GPIO_readPins(GYR_PORT, IIC_GYR_SDA_GYR_PIN)
#define GYR_IIC_SCL_READ (bool)DL_GPIO_readPins(GYR_PORT, IIC_GYR_SCL_GYR_PIN)

extern uint8_t GYR_IIC_DATA;

extern void GYR_IIC_init(void);
extern void GYR_IIC_start(void);
extern void GYR_IIC_stop(void);
extern void GYR_IIC_ACK(void);
extern void GYR_IIC_NACK(void);
extern unsigned char GYR_Check_ACK(void);
extern void GYR_IIC_Send_Byte(uint8_t Data);
extern unsigned char GYR_IIC_Read_Byte(uint8_t ack);
extern void GYR_IIC_reset(void);
extern uint8_t GYR_IIC_Read(uint8_t addr, uint8_t len, uint8_t *buf);
extern uint8_t GYR_IIC_Read_To_Mem(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
extern uint8_t GYR_IIC_Write(uint8_t addr, uint8_t len, uint8_t *buf);
extern uint8_t GYR_IIC_Write_To_Mem(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

#define GYR_IIC_delay delay_cycles(2000);

#endif
