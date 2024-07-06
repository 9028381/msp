#include "gyroscope.h"
#include "gyr_iic.h"

#define GYR_ADDR 0x50

float Get_gyr_value(enum gyroscope key) {
  uint8_t buf[2];

  IIC_Read_To_Mem(GYR_ADDR, key, 2, buf);
  float value = (short)(((short)buf[1] << 8) | buf[0]);

  switch (key) {
  case gyr_a_x:
  case gyr_a_y:
  case gyr_a_z:
    return value * 16 * 9.8;
  case gyr_w_x:
  case gyr_w_y:
  case gyr_w_z:
    return value / 2000;
  case gyr_x_roll:
  case gyr_y_pitch:
  case gyr_z_yaw:
    return value * 180 / 32768;
  }
}

/*
void GYR_calibrate() {
  uint8_t cmd_calibrate = 0x01;
  uint8_t cmd_work = 0x00;

  IIC_Write_To_Mem(GYR_ADDR, 0x01, 1, &cmd_calibrate);
  delay_ms(100);
  cmd_calibrate = 0x07;
  IIC_Write_To_Mem(GYR_ADDR, 0x01, 1, &cmd_calibrate);
  delay_ms(100);
  IIC_Write_To_Mem(GYR_ADDR, 0x01, 1, &cmd_work);
}
*/

/*
void GYR_set0() {
  uint8_t cmd_set0 = 0x04;
  uint8_t cmd_work = 0x00;
  uint8_t cmd_unlock[2] = {0x88, 0xB5};

  IIC_Write_To_Mem(GYR_ADDR, 0x69, 2, cmd_unlock);
  IIC_Write_To_Mem(GYR_ADDR, 0x01, 1, &cmd_work);
  delay_ms(200);
  IIC_Write_To_Mem(GYR_ADDR, 0x01, 1, &cmd_set0);
}
*/
