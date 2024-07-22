#include "iic-hardware.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti_msp_dl_config.h"

// 注意: DEV_ADDR是取右7位
void IIC_Write_HW(uint8_t DEV_ADDR, uint8_t size, uint8_t *pData) {
  /*
   * Fill FIFO with data. This example will send a MAX of 8 bytes since it
   * doesn't handle the case where FIFO is full
   */
  DL_I2C_fillControllerTXFIFO(I2C_INST, pData, size);

  /* Wait for I2C to be Idle */
  while (
      !(DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
    ;

  /* Send the packet to the controller.
   * This function will send Start + Stop automatically.
   */
  DL_I2C_startControllerTransfer(I2C_INST, DEV_ADDR,
                                 DL_I2C_CONTROLLER_DIRECTION_TX, size);

  /* Poll until the Controller writes all bytes */
  while (DL_I2C_getControllerStatus(I2C_INST) &
         DL_I2C_CONTROLLER_STATUS_BUSY_BUS)
    ;

  /* Wait for I2C to be Idle */
  while (
      !(DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
    ;

  /* Add delay between transfers */
  //delay_cycles(1000);   可能没用？？？？？？？？
}

void IIC_Read_HW(uint8_t DEV_ADDR, uint8_t size, uint8_t *pData) {
  /* Send a read request to Target */
  DL_I2C_startControllerTransfer(I2C_INST, DEV_ADDR,
                                 DL_I2C_CONTROLLER_DIRECTION_RX, size);

  /*
   * Receive all bytes from target. LED will remain high if not all bytes
   * are received
   */

  for (uint8_t i = 0; i < size; i++) {
    while (DL_I2C_isControllerRXFIFOEmpty(I2C_INST))
      ;
    pData[i] = DL_I2C_receiveControllerData(I2C_INST);
  }
}

void iic_hardware_write(uint8_t DEV_ADDR, uint8_t size, uint8_t *pData) {
  IIC_Write_HW(DEV_ADDR, size, pData);
}

void iic_handware_read(uint8_t DEV_ADDR, uint8_t size, uint8_t *pData) {
  IIC_Read_HW(DEV_ADDR, size, pData);
}
