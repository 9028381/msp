/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-04 10:47:57
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-04 11:06:27
 * @FilePath: \empty\user\encounter.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "encounter.h"

uint32_t L_1 = 0xefff;
uint32_t L_2 = 0xefff;
uint32_t L_3 = 0xefff;
uint32_t L_4 = 0xefff;

void init_encounter()
{
    L_1 = 0xefff;
    L_2 = 0xefff;
    L_3 = 0xefff;
    L_4 = 0xefff;

    NVIC_EnableIRQ(GPIOA_INT_IRQn);
    NVIC_EnableIRQ(GPIOB_INT_IRQn);

    return;
}


uint8_t M1_CH2_getValue(void) {

    uint8_t buf = 0;
    if (DL_GPIO_readPins(M1_M1_CH2_PORT, M1_M1_CH2_PIN)) {
      buf = 1;
    } else {
      buf = 0;
    }
    return buf;
}

uint8_t M2_CH2_getValue(void) {

    uint8_t buf = 0;
    if (DL_GPIO_readPins(M2_M2_CH2_PORT, M2_M2_CH2_PIN)) {
      buf = 1;
    } else {
      buf = 0;
    }
    return buf;
}

uint8_t M3_CH2_getValue(void) {

    uint8_t buf = 0;
    if (DL_GPIO_readPins(M3_M3_CH2_PORT, M3_M3_CH2_PIN)) {
      buf = 1;
    } else {
      buf = 0;
    }
    return buf;
}

uint8_t M4_CH2_getValue(void) {

    uint8_t buf = 0;
    if (DL_GPIO_readPins(M4_PORT, M4_M4_CH2_PIN)) {
      buf = 1;
    } else {
      buf = 0;
    }
    return buf;
}

void M1_CH1_INT(void)
{
  if (M1_CH2_getValue()) {
    L_1++;
  } else {
    L_1--;
  }
}

void M2_CH1_INT(void)
{
  if (M2_CH2_getValue()) {
    L_2++;
  } else {
    L_2--;
  }
}

void M3_CH1_INT(void)
{
  if (M3_CH2_getValue()) {
    L_3++;
  } else {
    L_3--;
  }
}

void M4_CH1_INT(void)
{
  if (M4_CH2_getValue()) {
    L_4++;
  } else {
    L_4--;
  }
}

