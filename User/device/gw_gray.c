#include "gw_gray.h"
#include "User/config.h"
#include "User/device/led.h"
#include "User/drive/iic-hardware.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "stdbool.h"
#include "ti_msp_dl_config.h"
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

short gw_gray_diff(uint8_t line) {
  static int maybe = 0;
  static uint8_t last = 0;
  static bool gw_single_1 = false;
  static bool gw_single_2 = false;
  short diff = 0;
  unsigned char cnt = 0;


  if (maybe == 0) {
    {
        if (gw_single_1){
      maybe = 1;
      last = line;
      return maybe * GW_SINGLE_BIT_WEIGHT;
        }else {
            gw_single_1 = true;
        }
    }
    if (1) {
        if (gw_single_2){
      maybe = -1;
      last = line;
      return maybe * GW_SINGLE_BIT_WEIGHT;
        } else {
        gw_single_2 = true;
        }
    } else {
        gw_single_2 = false;        
    }
  } else {
    if (line & 0b01111110)
      maybe = 0;
    else{
      last = line;
      return maybe * GW_SINGLE_BIT_WEIGHT;
    }
  }

  //   if (line == 0) {
  //     if ((status.times - last) < 3)
  //       times = times >= 5 ? 5 : times + 1;
  //     else
  //       times = 0;

  //     last = status.times;

  //     if (times >= 5) {
  //       return ROAD_NO;
  //     }

  //     return 0;
  //   }
  
  if (line == 0){
    if (last & 0b00111100 || last == 0){
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

  // gw_gray_show(line);

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
