#include "gw_gray.h"
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

const int16_t gw_bit_weight[8] = {0, -300, -150, -50, 50, 150, 300, 0};

short gw_gray_diff(uint8_t line) {
  short diff = 0;
  unsigned char cnt = 0;

  for (int i = 0; i < 8; i++) {
    if (((line >> i) & 0x01)) {
      cnt++;
      diff += gw_bit_weight[i];
    }
  }
  if (cnt != 0) {
    return diff / cnt;
  } else {
    return 0;
  }
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

#define INTEGRAL_TIMES 10
enum Road {           // L F R
  CrossRoad = 0b111,  // 1 1 1
  TBRoad = 0b101,     // 1 0 1
  TLRoad = 0b110,     // 1 1 0
  TRRoad = 0b011,     // 0 1 1
  LeftRoad = 0b100,   // 1 0 0
  RightRoad = 0b001,  // 0 0 1
  Straight = 0b010,   // 0 1 0
  UnknowRoad = 0b000, // 0 0 0
};
enum Road cross = Straight;

enum Road road_new_from_bit(bool L, bool F, bool R) {
  uint8_t left = L ? 0b100 : 0;
  uint8_t font = F ? 0b010 : 0;
  uint8_t right = R ? 0b001 : 0;

  return left | font | right;
}

void gw_gray_decision(uint8_t integral, uint8_t line) {
  bool left = (integral >> 6) == 0x03;    // 0b1100_0000
  bool right = (integral & 0x03) == 0x03; // 0b0000_0011
  bool font = line & 0x3C;                // 0b0011_1100
  enum Road road = road_new_from_bit(left, font, right);
  cross = road;
}

short gw_gray_get_diff() {
  static uint8_t maybe = 0;
  static uint8_t integral = 0;

  uint8_t line = gw_gray_get_line_digital_is_black();

  gw_gray_show(line);

  if (maybe) {
    if (maybe == 1) {
      if (cross == Straight)
        gw_gray_decision(integral, line);
      switch (cross) {
      case UnknowRoad:
        INFO("Unknow road");
        cross = Straight;
        maybe = 0;
        return 0;
      case CrossRoad:
        INFO("Cross road");
          cross = Straight;
          maybe = 0;
        return 0;
      case TBRoad:
        INFO("T B road");
          maybe = 1;
          status.base_speed = 0;
        return 0;
      case TLRoad:
        INFO("T L road");
          cross = Straight;
          maybe = 0;
        return 0;
      case TRRoad:
        INFO("T R road");
          cross = Straight;
          maybe = 0;
        return 0;
      case LeftRoad:
        INFO("Left road");
        if (line & 0b00111100) {
          cross = Straight;
          maybe = 0;
          return gw_gray_diff(line & 0x7E);
        }
        return 30000;
      case RightRoad:
        INFO("Right road");
        if (line & 0b00111100) {
          cross = Straight;
          maybe = 0;
          return gw_gray_diff(line & 0x7E);
        }
        return -30000;
      case Straight:
        INFO("Straight road");
        maybe = 0;
        return gw_gray_diff(line & 0x7E);
      }
    }

    integral = integral | line;
    maybe--;
  } else if (line & 0x81) {
    maybe = INTEGRAL_TIMES;
    integral = 0;
  }

  return gw_gray_diff(line & 0x7E); // 0b0111_1110
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
