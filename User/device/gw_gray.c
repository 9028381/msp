#include "gw_gray.h"
#include "User/config.h"
#include "User/device/led.h"
#include "User/drive/iic-hardware.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "stdbool.h"
#include <stdint.h>

#define GW_GRAY_ADDR 0x4C

#define Ping_CMD 0xAA
#define Ping_SUCCESS 0x66
#define Digital_Output_CMD 0xDD
#define Analogue_Output_CMD 0xB0
#define Get_error_CMD 0xDE

// const int16_t gw_bit_weight[8] = {0, -300, -100, -30, 30, 100, 300, 0};
// //直角参数
int16_t gw_bit_weight[8] = {-300, -250, -150, -70, 70, 150, 250, 300};

short gw_gray_diff(uint8_t line) {
  static unsigned char times = 0;
  static unsigned last = 0;
  short diff = 0;
  unsigned char cnt = 0;

  if (line == 0) {
    if (last - status.times < 3)
      times++;
    else
      times = 0;

    last = status.times;

    if (times == 5) {
      times = 0;
      return ROAD_NO;
    }

    return 0;
  }

  for (int i = 0; i < 8; i++) {
    if (((line >> i) & 0x01)) {
      cnt++;
      diff += gw_bit_weight[i];
    }
  }

  return diff / cnt;
}

void gw_gray_show(uint8_t line) {
  char str[9];
  str[8] = '\0';

  for (int i = 0; i < 8; i++) {
    str[i] = line & 0x80 ? '#' : '.';
    line <<= 1;
  }

  //   PRINTLN("%s", str);
}

short gw_gray_get_diff() {
  static uint8_t maybe = 0;
  static uint8_t integral = 0;
  static uint8_t ret_cnt = 0;

  uint8_t line = gw_gray_get_line_digital_is_black();

  //   gw_gray_show(line);

  return gw_gray_diff(line); // 0b0111_1110
}

uint8_t gw_gray_get_line_digital_is_black() {
  uint8_t cmd = Digital_Output_CMD;
  uint8_t buf = 0;
  iic_hardware_write(GW_GRAY_ADDR, 1, &cmd);
  iic_handware_read(GW_GRAY_ADDR, 1, &buf);

  return ~buf;
}

void gw_gray_get_line_analog(uint8_t gray[8]) {
  uint8_t cmd = Analogue_Output_CMD;
  iic_hardware_write(GW_GRAY_ADDR, 1, &cmd);
  iic_handware_read(GW_GRAY_ADDR, 8, gray);
  // printf("1:%X 2:%X 3:%X 4:%X 5:%X 6:%X 7:%X 8:%X", buf[0], buf[1], buf[2],
  // buf[3], buf[4], buf[5], buf[6], buf[7]);
}

uint8_t gw_gray_ping() {
  uint8_t cmd = Ping_CMD;
  //  uint8_t buf = IIC_Write(GW_GRAY_ADDR, 1, &cmd);
  //  IIC_Read(GW_GRAY_ADDR, 1, &buf);
  //  if (buf == Ping_SUCCESS)
  return 1;
  //  else
  //    return 0;
}

uint8_t gw_gray_get_error() {
  uint8_t cmd = Get_error_CMD;
  uint8_t buf = 0;
  iic_hardware_write(GW_GRAY_ADDR, 1, &cmd);
  iic_handware_read(GW_GRAY_ADDR, 1, &buf);

  return buf;
}
