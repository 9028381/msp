#include "gyroscope.h"
#include "gyr_iic.h"
#include "ti/driverlib/m0p/dl_core.h"

#define GYR_ADDR 0x50

float Get_gyr_value(enum gyroscope key) {
  uint8_t buf[2];

  GYR_IIC_Read_To_Mem(GYR_ADDR, key, 2, buf);
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

void GYR_unlock() {
  uint8_t buf[5] = {0xff, 0xaa, 0x69, 0x88, 0xb5};
  GYR_IIC_Write(GYR_ADDR, 5, buf);
}

void GYR_save() {
  uint8_t buf[5] = {0xff, 0xaa, 0x00, 0x00, 0x00};
  GYR_IIC_Write(GYR_ADDR, 5, buf);
}

void GYR_set0(enum gyroscope tar) {
  if (tar == gyr_y_pitch) {
    GYR_unlock();
    uint8_t buf[5] = {0xff, 0xaa, 0x01, 0x40, 0x00};
    GYR_IIC_Write(GYR_ADDR, 5, buf);
    GYR_save();
  }
}
