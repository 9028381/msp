/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-04 11:35:13
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-05 17:15:41
 * @FilePath: \empty\user\motor.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "motor.h"
#include "control-center.h"
#include "encounter.h"
#include "ti/driverlib/dl_comp.h"
#include "ti/driverlib/dl_gpio.h"
#include "utils/pid.h"

#define MAX_P 9999

Pid M_F_L_PID;
Pid M_F_R_PID;
Pid M_B_L_PID;
Pid M_B_R_PID;

void init_PID() {

  pid_init(&M_F_L_PID, 1, 1, 1, 5, 50);
  pid_init(&M_F_R_PID, 1, 1, 1, 5, 50);
  pid_init(&M_B_L_PID, 10, 10, 10, 5, 50);
  pid_init(&M_B_R_PID, 10, 10, 10, 5, 50);
}

int32_t get_speed(enum MOTOR M) {
  int32_t speed = 0;
  if (M == M_F_L) {
    speed = L_1 - 0xefff;
    L_1 = 0xefff;
  }
  if (M == M_F_R) {
    speed = L_2 - 0xefff;
    L_2 = 0xefff;
  }
  if (M == M_B_L) {
    speed = L_3 - 0xefff;
    L_3 = 0xefff;
  }
  if (M == M_B_R) {
    speed = L_4 - 0xefff;
    L_4 = 0xefff;
  }
  return speed;
}

void set_direction(enum MOTOR M, int32_t pid_return) {
  if (M == M_F_L) {
    if (pid_return > 0) {
      DL_GPIO_setPins(M1_M1_D1_PORT, M1_M1_D1_PIN);
      DL_GPIO_clearPins(M1_M1_D2_PORT, M1_M1_D2_PIN);
    } else if (pid_return < 0) {
      DL_GPIO_setPins(M1_M1_D2_PORT, M1_M1_D2_PIN);
      DL_GPIO_clearPins(M1_M1_D1_PORT, M1_M1_D1_PIN);
    } else {
      DL_GPIO_clearPins(M1_M1_D1_PORT, M1_M1_D1_PIN);
      DL_GPIO_clearPins(M1_M1_D2_PORT, M1_M1_D2_PIN);
    }
  } else if (M == M_F_R) {
    if (pid_return > 0) {
      DL_GPIO_setPins(M2_M2_D1_PORT, M2_M2_D1_PIN);
      DL_GPIO_clearPins(M2_M2_D2_PORT, M2_M2_D2_PIN);
    } else if (pid_return < 0) {
      DL_GPIO_setPins(M2_M2_D2_PORT, M2_M2_D2_PIN);
      DL_GPIO_clearPins(M2_M2_D1_PORT, M2_M2_D1_PIN);
    } else {
      DL_GPIO_clearPins(M2_M2_D1_PORT, M2_M2_D1_PIN);
      DL_GPIO_clearPins(M2_M2_D2_PORT, M2_M2_D2_PIN);
    }
  } else if (M == M_B_L) {
    if (pid_return > 0) {
      DL_GPIO_setPins(M3_M3_D1_PORT, M3_M3_D1_PIN);
      DL_GPIO_clearPins(M3_M3_D2_PORT, M3_M3_D2_PIN);
    } else if (pid_return < 0) {
      DL_GPIO_setPins(M3_M3_D2_PORT, M3_M3_D2_PIN);
      DL_GPIO_clearPins(M3_M3_D1_PORT, M3_M3_D1_PIN);
    } else {
      DL_GPIO_clearPins(M3_M3_D1_PORT, M3_M3_D1_PIN);
      DL_GPIO_clearPins(M3_M3_D2_PORT, M3_M3_D2_PIN);
    }
  } else if (M == M_B_R) {
    if (pid_return > 0) {
      DL_GPIO_setPins(M4_PORT, M4_M4_D1_PIN);
      DL_GPIO_clearPins(M4_PORT, M4_M4_D2_PIN);
    } else if (pid_return < 0) {
      DL_GPIO_setPins(M4_PORT, M4_M4_D2_PIN);
      DL_GPIO_clearPins(M4_PORT, M4_M4_D1_PIN);
    } else {
      DL_GPIO_clearPins(M4_PORT, M4_M4_D1_PIN);
      DL_GPIO_clearPins(M4_PORT, M4_M4_D2_PIN);
    }
  }
}

int32_t abs(int32_t B) {
  if (B <= 0) {
    return -B;
  } else {
    return B;
  }
}

int32_t M_F_L_P = 0;
int32_t M_F_R_P = 0;
int32_t M_B_L_P = 0;
int32_t M_B_R_P = 0;

int32_t set_confine(int32_t num) {
  if (num > MAX_P) {
    return MAX_P;
  } else if (num < -MAX_P) {
    return -MAX_P;
  } else {
    return num;
  }
} // 设置占空比的范围不超过 MAX_P

void pid_keep_speed() {
  M_F_L_P += pid_compute(&M_F_L_PID, M_F_L_tar, M_F_L_cur);
  M_F_R_P += pid_compute(&M_F_R_PID, M_F_R_tar, M_F_R_cur);
  M_B_L_P += pid_compute(&M_B_L_PID, M_B_L_tar, M_B_L_cur);
  M_B_R_P += pid_compute(&M_B_R_PID, M_B_R_tar, M_B_R_cur);
  //   pid_set_target(&m_fl_pid, M_F_L_tar);
  //   M_F_L_P += pid_inc(&m_fl_pid, M_F_L_cur);
  //   pid_set_target(&m_fr_pid, M_F_R_tar);
  //   M_F_R_P += pid_inc(&m_fr_pid, M_F_R_cur);
  //   pid_set_target(&m_bl_pid, M_B_L_tar);
  //   M_B_L_P += pid_inc(&m_bl_pid, M_B_L_cur);
  //   pid_set_target(&m_br_pid, M_B_R_tar);
  //   M_B_R_P += pid_inc(&m_br_pid, M_B_R_cur);

  M_F_L_P = set_confine(M_F_L_P);
  M_F_R_P = set_confine(M_F_R_P);
  M_B_L_P = set_confine(M_B_L_P);
  M_B_R_P = set_confine(M_B_R_P);

  set_direction(M_F_L, M_F_L_P);
  set_direction(M_F_R, M_F_R_P);
  set_direction(M_B_L, M_B_L_P);
  set_direction(M_B_R, M_B_R_P);

  DL_Timer_setCaptureCompareValue(M_PWM_INST, abs(M_F_L_P),
                                  DL_TIMER_CC_0_INDEX);
  DL_Timer_setCaptureCompareValue(M_PWM_INST, abs(M_F_R_P),
                                  DL_TIMER_CC_1_INDEX);
  DL_Timer_setCaptureCompareValue(M_PWM_INST, abs(M_B_L_P),
                                  DL_TIMER_CC_2_INDEX);
  DL_Timer_setCaptureCompareValue(M_PWM_INST, abs(M_B_R_P),
                                  DL_TIMER_CC_3_INDEX);

  return;
}
