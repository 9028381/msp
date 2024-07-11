/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-07 18:11:54
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-07 19:51:32
 * @FilePath: \empty\user\uart_re_driver.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "uart_re_driver.h"
#include "device/uart.h"
#include "status/rpc.h"
#include "status/status.h"
#include "stdint.h"
#include "utils/log.h"

uint8_t R1_BUFF[4] = {0};
uint8_t R2_BUFF[4] = {0};
uint8_t R3_BUFF[4] = {0};
uint8_t R4_BUFF[4] = {0};

uint8_t R1_flag = 0;
uint8_t R2_flag = 0;
uint8_t R3_flag = 0;
uint8_t R4_flag = 0;

void uart_re_driver(enum Uart uart, uint8_t data) {
  if (uart == uart1) {
    if (R1_flag == 0) {
      if (data == 0xff) {
        R1_BUFF[R1_flag] = data;
        R1_flag++;
      }
    } else {
      R1_BUFF[R1_flag++] = data;
      if (R1_flag == 4) {
        uint16_t cat = ((uint16_t)R1_BUFF[2] << 8) | R1_BUFF[3];
        rpc_call_id(status.rpc, R1_BUFF[1], cat);

        for (int i = 0; i < 4; i++) {
          R1_BUFF[i] = 0;
        }
        R1_flag = 0;
      }
    }
  }
  if (uart == uart2) {
    if (R2_flag == 0) {
      if (data == 0xff) {
        R2_BUFF[R2_flag] = data;
        R2_flag++;
      }
    } else {
      R2_BUFF[R2_flag++] = data;
      if (R2_flag == 4) {
                uint16_t cat = ((uint16_t)R2_BUFF[2] << 8) | R2_BUFF[3];
        rpc_call_id(status.rpc, R2_BUFF[1], cat);

        for (int i = 0; i < 4; i++) {
          R2_BUFF[i] = 0;
        }
        R2_flag = 0;
      }
    }
  }
  if (uart == uart3) {
    if (R3_flag == 0) {
      if (data == 0xff) {
        R3_BUFF[R3_flag] = data;
        R3_flag++;
      }
    } else {
      R3_BUFF[R3_flag++] = data;
      if (R3_flag == 4) {
                uint16_t cat = ((uint16_t)R3_BUFF[2] << 8) | R3_BUFF[3];
        rpc_call_id(status.rpc, R3_BUFF[1], cat);

        for (int i = 0; i < 4; i++) {
          R3_BUFF[i] = 0;
        }
        R3_flag = 0;
      }
    }
  }
  if (uart == uart4) {
    if (R4_flag == 0) {
      if (data == 0xff) {
        R4_BUFF[R4_flag] = data;
        R4_flag++;
      }
    } else {
      R4_BUFF[R4_flag++] = data;
      if (R4_flag == 4) {
                uint16_t cat = ((uint16_t)R4_BUFF[2] << 8) | R4_BUFF[3];
        rpc_call_id(status.rpc, R4_BUFF[1], cat);

        for (int i = 0; i < 4; i++) {
          R4_BUFF[i] = 0;
        }
        R4_flag = 0;
      }
    }
  }
}
