#include "gw_gray.h"
#include "User/iic_hw.h"


#define GW_GRAY_ADDR 0x4C

#define Ping_CMD 0xAA
#define Ping_SUCCESS 0x66
#define Digital_Output_CMD 0xDD
#define Analogue_Output_CMD 0xB0
#define Get_error_CMD 0xDE

uint8_t gw_gray_get_line_digital_is_black() {
  uint8_t cmd = Digital_Output_CMD;
  uint8_t buf = 0;
  IIC_Write_HW(GW_GRAY_ADDR, 1, &cmd);
  IIC_Read_HW(GW_GRAY_ADDR, 1, &buf);
  return ~buf;
}

void gw_gray_get_line_analog(uint8_t gray[8]) {
  uint8_t cmd = Analogue_Output_CMD;
  IIC_Write_HW(GW_GRAY_ADDR, 1, &cmd);
  IIC_Read_HW(GW_GRAY_ADDR, 8, gray);
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
  IIC_Write_HW(GW_GRAY_ADDR, 1, &cmd);
  IIC_Read_HW(GW_GRAY_ADDR, 1, &buf);

  return buf;
}
