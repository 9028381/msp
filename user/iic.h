#ifndef __IIC_H_
#define __IIC_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "empty/ti_msp_dl_config.h"

#define GYR_PORT IIC_GYR_PORT
#define GYR_SDA IIC_GYR_SDA_PIN
#define GYR_SCL IIC_GYR_SCL_PIN

#define IIC_SCL_OUT DL_GPIO_initDigitalOutput(IIC_SCL_IOMUX)
#define IIC_SCL_IN DL_GPIO_initDigitalInput(IIC_SCL_IOMUX)
#define IIC_SDA_OUT DL_GPIO_initDigitalOutput(IIC_SDA_IOMUX)
#define IIC_SDA_IN DL_GPIO_initDigitalInput(IIC_SDA_IOMUX)

#define IIC_SCL_HIGH DL_GPIO_setPins(IIC_PORT, IIC_SCL_PIN)
#define IIC_SCL_LOW DL_GPIO_clearPins(IIC_PORT, IIC_SCL_PIN)

#define IIC_SDA_HIGH DL_GPIO_setPins(IIC_PORT, IIC_SDA_PIN)
#define IIC_SDA_LOW DL_GPIO_clearPins(IIC_PORT, IIC_SDA_PIN)

#define IIC_SDA_READ (bool)DL_GPIO_readPins(IIC_PORT, IIC_SDA_PIN)
#define IIC_SCL_READ (bool)DL_GPIO_readPins(IIC_PORT, IIC_SCL_PIN)

extern uint8_t IIC_DATA;

extern void IIC_init(void);
extern void IIC_start(void);
extern void IIC_stop(void);
extern void IIC_ACK(void);
extern void IIC_NACK(void);
extern unsigned char Check_ACK(void);
extern void IIC_Send_Byte(uint8_t Data);
extern unsigned char IIC_Read_Byte(uint8_t ack);
extern void IIC_reset(void);
extern uint8_t IIC_Read(uint8_t addr, uint8_t len, uint8_t *buf);
extern uint8_t IIC_Read_To_Mem(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
extern uint8_t IIC_Write(uint8_t addr, uint8_t len, uint8_t *buf);
extern uint8_t IIC_Write_To_Mem(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

#define IIC_delay delay_cycles(20000);

#endif
