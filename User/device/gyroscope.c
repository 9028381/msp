#include "gyroscope.h"
#include "User/drive/iic-software.h"

#define GYR_ADDR 0x50

float gyr_get_value(enum Gyroscope key) {
  uint8_t buf[2];

  iic_software_read_to_mem(GYR_ADDR, key, 2, buf);
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

void gyr_unlock() {
  uint8_t buf[5] = {0xff, 0xaa, 0x69, 0x88, 0xb5};
  iic_software_write(GYR_ADDR, 5, buf);
}

void gyr_save() {
  uint8_t buf[5] = {0xff, 0xaa, 0x00, 0x00, 0x00};
  iic_software_write(GYR_ADDR, 5, buf);
}

void gyr_set_zero(enum Gyroscope tar) {
  if (tar == gyr_y_pitch) {
    gyr_unlock();
    uint8_t buf[5] = {0xff, 0xaa, 0x01, 0x40, 0x00};
    iic_software_write(GYR_ADDR, 5, buf);
    gyr_save();
  }
}
