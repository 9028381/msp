#include "gw_gray.h"
#include "User/drive/iic-hardware.h"
#include "User/task/task.h"
#include "User/utils/log.h"
#include "stdbool.h"
#include "User/device/led.h"
#include <stdint.h>

#define GW_GRAY_ADDR 0x4C

#define Ping_CMD 0xAA
#define Ping_SUCCESS 0x66
#define Digital_Output_CMD 0xDD
#define Analogue_Output_CMD 0xB0
#define Get_error_CMD 0xDE

const int16_t gw_bit_weight[8] = {0, -1500, -300, -100, 100, 300, 1500, 0};

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

uint8_t gw_read_line_buf = 0;
bool gw_cross_block = false;
enum Crossing { Cross, TRoad, LeftTurn, RightTurn, Straight };
enum Crossing cross = Straight;
enum Crossing gw_TRoad_as = RightTurn;
enum Crossing gw_Cross_as = Straight;

void crossing_R_decision(void *para);
void crossing_L_decision(void *para);
void crossing_T_decision(void *para);

void crossing_L_decision(void *para) {
  uint32_t data = (uint32_t)para;
  data -= 1;

  if (data == 0) {
    if (gw_read_line_buf & 0x01)
      cross = gw_TRoad_as;
    else
      cross = LeftTurn;
    return;
  }

  if (gw_read_line_buf & 0x01) {
    Task t = task_new(crossing_T_decision, (void *)data);
    task_timed_append(&task.timed, t, 1);
    return;
  }

  Task t = task_new(crossing_L_decision, (void *)data);
  task_timed_append(&task.timed, t, 1);
}

void crossing_R_decision(void *para) {
  uint32_t data = (uint32_t)para;
  data -= 1;

  if (data == 0) {
    if (gw_read_line_buf & 0x80)
      cross = gw_TRoad_as;
    else
      cross = RightTurn;
    return;
  }

  if (gw_read_line_buf & 0x80) {
    Task t = task_new(crossing_T_decision, (void *)data);
    task_timed_append(&task.timed, t, 1);
    return;
  }

  Task t = task_new(crossing_R_decision, (void *)data);
  task_timed_append(&task.timed, t, 1);
}

void crossing_T_decision(void *para) {
  uint32_t data = (uint32_t)para;
  data -= 1;

  if (data == 0) {
    led_blame(0, 5, 5, 5);
    if (gw_read_line_buf & 0x7E)
      cross = gw_Cross_as;
    else
      cross = gw_TRoad_as;
    return;
  }

  Task t = task_new(crossing_L_decision, (void *)data);
  task_timed_append(&task.timed, t, 1);
}

short gw_gray_get_diff() {
  static enum Crossing maybe = Straight;

  uint8_t line = gw_gray_get_line_digital_is_black();
  
  char out_8[9] = {0};
  int i;
  for(i=7;i>=0;i--)
  {
     if((line >> i) & 0x01)
       out_8[7-i] = '#';
     else
       out_8[7-i] = '.';
  }
 PRINTLN("%s", out_8);

  gw_read_line_buf = line;

  if ((line & 0x81) && !gw_cross_block) {
    // This variable determines how many times the judgment is made.
    gw_cross_block = true;
    uint32_t para = 6;
    Task t;
    switch (line & 0x81) {
    case 0x01:
      t = task_new(crossing_R_decision, (void *)para);
      task_timed_append(&task.timed, t, 1);
      break;
    case 0x80:
      t = task_new(crossing_L_decision, (void *)para);
      task_timed_append(&task.timed, t, 1);
      break;
    case 0x81:
      t = task_new(crossing_T_decision, (void *)para);
      task_timed_append(&task.timed, t, 1);
      break;
    }
  }

  switch (cross) {
  case RightTurn:
    return -30000;
  case LeftTurn:
    return 30000;
  default:
    return gw_gray_diff(line & 0x7E); // 0b0111_1110
  }
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
