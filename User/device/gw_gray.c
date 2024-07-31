#include "gw_gray.h"
#include "User/config.h"
#include "User/device/led.h"
#include "User/drive/iic-hardware.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "stdbool.h"
#include "ti_msp_dl_config.h"
#include <stdbool.h>
#include <stdint.h>

#define GW_GRAY_ADDR 0x4C

#define Ping_CMD 0xAA
#define Ping_SUCCESS 0x66
#define Digital_Output_CMD 0xDD
#define Analogue_Output_CMD 0xB0
#define Get_error_CMD 0xDE

// const int16_t gw_bit_weight[8] = {0, -300, -100, -30, 30, 100, 300, 0};
// //直角参数
// int16_t gw_bit_weight[8] = {-250, -250, -150, -70, 70, 150, 250, 250};
int16_t gw_bit_weight[8] = {-35, -25, -15, -7, 7, 15, 25, 35};
#define GW_SINGLE_BIT_WEIGHT 100

#ifdef OLD_GW_GRAY_DIFF
short gw_gray_diff(uint8_t line) {
  static int maybe = 0;
  static uint8_t last = 0;
  static bool gw_single_1 = false;
  static bool gw_single_2 = false;
  short diff = 0;
  unsigned char cnt = 0;

  if (maybe) {
    if (line & 0b01111110)
      maybe = 0;
    else {
      last = line;
      return maybe * GW_SINGLE_BIT_WEIGHT;
    }
  }

  if (line == 0) {
    if (last & 0b00111100 || last == 0) {
      last = line;
      return ROAD_NO;
    }
    int left = last & 0b11000000 ? 1 : 0;
    int right = last & 0b00000011 ? 1 : 0;
    maybe = left - right;
    last = line;
    return maybe * GW_SINGLE_BIT_WEIGHT;
  }

  for (int i = 0; i < 8; i++) {
    if (((line >> i) & 0x01)) {
      cnt++;
      diff += gw_bit_weight[i];
    }
  }

  last = line;
  return diff / cnt;
}
#endif

short gw_point_weight_mul(uint8_t line) {
  short diff = 0;
  unsigned char cnt = 0;

  if (line == 0)
    return ROAD_NO;

  for (int i = 0; i < 8; i++) {
    if (((line >> i) & 0x01)) {
      cnt++;
      diff += gw_bit_weight[i];
    }
  }

  return diff / cnt;
}

short gw_gray_diff(uint8_t line) {
  static uint8_t last = 0;
  uint8_t rshift = (last >> 1) & line;
  uint8_t lshift = (last << 1) & line;

  last = line;
  uint8_t ret = rshift | lshift | line;

  if (ret == 0)
    return ROAD_NO;

  return gw_point_weight_mul(ret);
}

void gw_gray_show(uint8_t line) {
  char str[9];
  str[8] = '\0';

  for (int i = 0; i < 8; i++) {
    str[i] = line & 0x80 ? '#' : '.';
    line <<= 1;
  }

  PRINTLN("%s", str);
}

short gw_gray_get_diff() {
  static uint8_t maybe = 0;
  static uint8_t integral = 0;
  static uint8_t ret_cnt = 0;

  uint8_t line = gw_gray_get_line_digital_is_black();

  /* gw_gray_show(line); */

  return gw_gray_diff(line); // 0b0111_1110
}

short gw_gray_get_raw_integral() {
  static uint8_t last = 0;
  uint8_t line = gw_gray_get_line_digital_is_black();
  uint8_t rshift = (last >> 1) & line;
  uint8_t lshift = (last << 1) & line;

  last = line;
  /* gw_gray_show(line); */
  return rshift | lshift | line;
}

uint8_t gw_gray_get_line_digital_is_black() {
  uint8_t cmd = Digital_Output_CMD;
  uint8_t buf = 0;
  iic_hardware_write(GW_GRAY_ADDR, 1, &cmd);
  //   iic_handware_read(GW_GRAY_ADDR, 1, &buf);
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_1_PORT, GRAY8_PIN_1_PIN) << 7;
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_2_PORT, GRAY8_PIN_2_PIN) << 6;
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_3_PORT, GRAY8_PIN_3_PIN) << 5;
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_4_PORT, GRAY8_PIN_4_PIN) << 4;
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_5_PORT, GRAY8_PIN_5_PIN) << 3;
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_6_PORT, GRAY8_PIN_6_PIN) << 2;
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_7_PORT, GRAY8_PIN_7_PIN) << 1;
  buf = buf | (bool)DL_GPIO_readPins(GRAY8_PIN_8_PORT, GRAY8_PIN_8_PIN);

  return buf;
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
