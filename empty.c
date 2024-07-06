/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-06-17 17:13:16
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-06 10:21:34
 * @FilePath: \empty\empty.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "control-center.h"
#include "encounter.h"
#include "gy901.h"
#include "motor.h"
#include "pid.h"
#include "servo.h"
#include "stdlib.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_dma.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "user/servo.h"
#include <stdio.h>
#include "utils/log.h"

int main(void) {
  SYSCFG_DL_init();

  //
  init_encounter();
  // init_PID();
  NVIC_EnableIRQ(TIMER_INT_INST_INT_IRQN);
  DL_TimerG_startCounter(TIMER_INT_INST);
  //
  //
  M_F_L_tar = 200;
  M_F_R_tar = 200;

  //	DL_SYSCTL_enableSleepOssnExit();

  while (1) {
    delay_cycles(99999999);
  }
}

void GROUP1_IRQHandler(void) {
  uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, M1_M1_CH1_PIN);
  uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(
      GPIOB, M2_M2_CH1_PIN | M3_M3_CH1_PIN | M4_M4_CH1_PIN);

  if ((gpioA & M1_M1_CH1_PIN) == M1_M1_CH1_PIN) {
    M1_CH1_INT();
    DL_GPIO_clearInterruptStatus(GPIOA, M1_M1_CH1_PIN);
  }
  if ((gpioB & M2_M2_CH1_PIN) == M2_M2_CH1_PIN) {
    M2_CH1_INT();
    DL_GPIO_clearInterruptStatus(GPIOB, M2_M2_CH1_PIN);
  }
  if ((gpioB & M3_M3_CH1_PIN) == M3_M3_CH1_PIN) {
    M3_CH1_INT();
    DL_GPIO_clearInterruptStatus(GPIOB, M3_M3_CH1_PIN);
  }
  if ((gpioB & M4_M4_CH1_PIN) == M4_M4_CH1_PIN) {
    M4_CH1_INT();
    DL_GPIO_clearInterruptStatus(GPIOB, M4_M4_CH1_PIN);
  }
}

void TIMER_INT_INST_IRQHandler(void) {
  switch (DL_TimerG_getPendingInterrupt(TIMER_INT_INST)) {
  case DL_TIMER_IIDX_ZERO:
    // M_F_L_cur = get_speed(M_F_L);
    // M_F_R_cur = get_speed(M_F_R);
    // pid_keep_speed();
    // printTo(1, "%d\r\n", M_F_L_cur);
    // printTo(1, "%f\r\n", Get_gyr_value(gyr_z_yaw));
		  log_uprintf(uart1, "Hello World!\r\n");
	  log_uprintf(uart1, "%d\r\n", M_F_L_cur);
	//log_uprintf(uart1, "%f\r\n", 3.14);
	
	  //uart_send(uart1, "Hello World!\r\n\n\n", 15);
		//uart_send(uart1, "AAAAAAAAAAA\r\n\n\n", 15);
		//uart_send(uart1, "BBBBBBBBBBB\r\n\n\n", 15);

    break;
  default:
    break;
  }
}
