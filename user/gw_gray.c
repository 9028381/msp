#include "gw_gray.h"
#include "iic.h"

//#define GW_GRAY_ADDR 0x4C >> 1
#define GW_GRAY_ADDR 0x4C


#define Ping_CMD 0xAA
#define Ping_SUCCESS 0x66
#define Digital_Output_CMD 0xDD
#define Analogue_Output_CMD 0xB0
#define Get_error_CMD 0xDE

uint8_t gw_gray_get_line_digital_is_black() {
  uint8_t cmd = Digital_Output_CMD;
  uint8_t buf = 0;
//  IIC_Write(GW_GRAY_ADDR, 1, &cmd);
//  IIC_Read(GW_GRAY_ADDR, 1, &buf);
  return ~buf;
}

uint8_t TEST_gw_gray_get_line_digital_is_black() {
  uint8_t cmd = Digital_Output_CMD;
  uint8_t buf = 0;
	
  /*
     * Fill FIFO with data. This example will send a MAX of 8 bytes since it
     * doesn't handle the case where FIFO is full
     */
    DL_I2C_fillControllerTXFIFO(I2C_INST, &cmd, 1);

    /* Wait for I2C to be Idle */
    while (!(
        DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
        ;

    /* Send the packet to the controller.
     * This function will send Start + Stop automatically.
     */
    DL_I2C_startControllerTransfer(I2C_INST, GW_GRAY_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_TX, 1);

    /* Poll until the Controller writes all bytes */
    while (DL_I2C_getControllerStatus(I2C_INST) &
           DL_I2C_CONTROLLER_STATUS_BUSY_BUS)
        ;

    /* Wait for I2C to be Idle */
    while (!(
        DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
        ;

    /* Add delay between transfers */
    delay_cycles(1000);

    /* Send a read request to Target */
    DL_I2C_startControllerTransfer(I2C_INST, GW_GRAY_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_RX, 1);

    /*
     * Receive all bytes from target. LED will remain high if not all bytes
     * are received
     */
        while (DL_I2C_isControllerRXFIFOEmpty(I2C_INST))
            ;
        buf = DL_I2C_receiveControllerData(I2C_INST);
    
	
	
  return ~buf;
}



void gw_gray_get_line_analog(uint8_t gray[8]) {
  uint8_t cmd = Analogue_Output_CMD;
//  IIC_Write(GW_GRAY_ADDR, 1, &cmd);
//  IIC_Read(GW_GRAY_ADDR, 8, gray);
  // printf("1:%X 2:%X 3:%X 4:%X 5:%X 6:%X 7:%X 8:%X", buf[0], buf[1], buf[2],
  // buf[3], buf[4], buf[5], buf[6], buf[7]);
}

uint8_t gw_gray_ping() {
  uint8_t cmd = Ping_CMD;
//  uint8_t buf = IIC_Write(GW_GRAY_ADDR, 1, &cmd);
	uint8_t buf = 0;
//  IIC_Read(GW_GRAY_ADDR, 1, &buf);
  if (buf == Ping_SUCCESS)
    return 1;
  else
    return 0;
}

uint8_t gw_gray_get_error() {
  uint8_t cmd = Get_error_CMD;
  uint8_t buf = 0;
//  IIC_Write(GW_GRAY_ADDR, 1, &cmd);
//  IIC_Read(GW_GRAY_ADDR, 1, &buf);

  return buf;
}
