/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for M_PWM */
#define M_PWM_INST                                                         TIMA0
#define M_PWM_INST_IRQHandler                                   TIMA0_IRQHandler
#define M_PWM_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define M_PWM_INST_CLK_FREQ                                             32000000
/* GPIO defines for channel 0 */
#define GPIO_M_PWM_C0_PORT                                                 GPIOB
#define GPIO_M_PWM_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_M_PWM_C0_IOMUX                                      (IOMUX_PINCM25)
#define GPIO_M_PWM_C0_IOMUX_FUNC                     IOMUX_PINCM25_PF_TIMA0_CCP0
#define GPIO_M_PWM_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_M_PWM_C1_PORT                                                 GPIOB
#define GPIO_M_PWM_C1_PIN                                          DL_GPIO_PIN_9
#define GPIO_M_PWM_C1_IOMUX                                      (IOMUX_PINCM26)
#define GPIO_M_PWM_C1_IOMUX_FUNC                     IOMUX_PINCM26_PF_TIMA0_CCP1
#define GPIO_M_PWM_C1_IDX                                    DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 2 */
#define GPIO_M_PWM_C2_PORT                                                 GPIOB
#define GPIO_M_PWM_C2_PIN                                         DL_GPIO_PIN_12
#define GPIO_M_PWM_C2_IOMUX                                      (IOMUX_PINCM29)
#define GPIO_M_PWM_C2_IOMUX_FUNC                     IOMUX_PINCM29_PF_TIMA0_CCP2
#define GPIO_M_PWM_C2_IDX                                    DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 3 */
#define GPIO_M_PWM_C3_PORT                                                 GPIOB
#define GPIO_M_PWM_C3_PIN                                         DL_GPIO_PIN_13
#define GPIO_M_PWM_C3_IOMUX                                      (IOMUX_PINCM30)
#define GPIO_M_PWM_C3_IOMUX_FUNC                     IOMUX_PINCM30_PF_TIMA0_CCP3
#define GPIO_M_PWM_C3_IDX                                    DL_TIMER_CC_3_INDEX

/* Defines for SERVO */
#define SERVO_INST                                                         TIMG6
#define SERVO_INST_IRQHandler                                   TIMG6_IRQHandler
#define SERVO_INST_INT_IRQN                                     (TIMG6_INT_IRQn)
#define SERVO_INST_CLK_FREQ                                               160000
/* GPIO defines for channel 0 */
#define GPIO_SERVO_C0_PORT                                                 GPIOA
#define GPIO_SERVO_C0_PIN                                         DL_GPIO_PIN_21
#define GPIO_SERVO_C0_IOMUX                                      (IOMUX_PINCM46)
#define GPIO_SERVO_C0_IOMUX_FUNC                     IOMUX_PINCM46_PF_TIMG6_CCP0
#define GPIO_SERVO_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_SERVO_C1_PORT                                                 GPIOA
#define GPIO_SERVO_C1_PIN                                         DL_GPIO_PIN_22
#define GPIO_SERVO_C1_IOMUX                                      (IOMUX_PINCM47)
#define GPIO_SERVO_C1_IOMUX_FUNC                     IOMUX_PINCM47_PF_TIMG6_CCP1
#define GPIO_SERVO_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_INT */
#define TIMER_INT_INST                                                   (TIMG0)
#define TIMER_INT_INST_IRQHandler                               TIMG0_IRQHandler
#define TIMER_INT_INST_INT_IRQN                                 (TIMG0_INT_IRQn)
#define TIMER_INT_INST_LOAD_VALUE                                        (6249U)




/* Defines for I2C */
#define I2C_INST                                                            I2C1
#define I2C_INST_IRQHandler                                      I2C1_IRQHandler
#define I2C_INST_INT_IRQN                                          I2C1_INT_IRQn
#define I2C_BUS_SPEED_HZ                                                  100000
#define GPIO_I2C_SDA_PORT                                                  GPIOA
#define GPIO_I2C_SDA_PIN                                          DL_GPIO_PIN_16
#define GPIO_I2C_IOMUX_SDA                                       (IOMUX_PINCM38)
#define GPIO_I2C_IOMUX_SDA_FUNC                        IOMUX_PINCM38_PF_I2C1_SDA
#define GPIO_I2C_SCL_PORT                                                  GPIOA
#define GPIO_I2C_SCL_PIN                                          DL_GPIO_PIN_15
#define GPIO_I2C_IOMUX_SCL                                       (IOMUX_PINCM37)
#define GPIO_I2C_IOMUX_SCL_FUNC                        IOMUX_PINCM37_PF_I2C1_SCL


/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOB
#define GPIO_UART_2_TX_PORT                                                GPIOB
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_18
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM44)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM43)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM44_PF_UART2_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM43_PF_UART2_TX
#define UART_2_BAUD_RATE                                                (460800)
#define UART_2_IBRD_32_MHZ_460800_BAUD                                       (4)
#define UART_2_FBRD_32_MHZ_460800_BAUD                                      (22)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART3
#define UART_1_INST_IRQHandler                                  UART3_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                        DL_GPIO_PIN_13
#define GPIO_UART_1_TX_PIN                                        DL_GPIO_PIN_14
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM35)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM36)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM35_PF_UART3_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM36_PF_UART3_TX
#define UART_1_BAUD_RATE                                                (115200)
#define UART_1_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_1_FBRD_32_MHZ_115200_BAUD                                      (23)
/* Defines for UART_4 */
#define UART_4_INST                                                        UART1
#define UART_4_INST_IRQHandler                                  UART1_IRQHandler
#define UART_4_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_4_RX_PORT                                                GPIOA
#define GPIO_UART_4_TX_PORT                                                GPIOA
#define GPIO_UART_4_RX_PIN                                        DL_GPIO_PIN_18
#define GPIO_UART_4_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_4_IOMUX_RX                                     (IOMUX_PINCM40)
#define GPIO_UART_4_IOMUX_TX                                     (IOMUX_PINCM39)
#define GPIO_UART_4_IOMUX_RX_FUNC                      IOMUX_PINCM40_PF_UART1_RX
#define GPIO_UART_4_IOMUX_TX_FUNC                      IOMUX_PINCM39_PF_UART1_TX
#define UART_4_BAUD_RATE                                                  (9600)
#define UART_4_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_4_FBRD_32_MHZ_9600_BAUD                                        (21)
/* Defines for UART_3 */
#define UART_3_INST                                                        UART0
#define UART_3_INST_IRQHandler                                  UART0_IRQHandler
#define UART_3_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_3_RX_PORT                                                GPIOA
#define GPIO_UART_3_TX_PORT                                                GPIOA
#define GPIO_UART_3_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_3_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_3_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_3_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_3_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_3_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_3_BAUD_RATE                                                (460800)
#define UART_3_IBRD_32_MHZ_460800_BAUD                                       (4)
#define UART_3_FBRD_32_MHZ_460800_BAUD                                      (22)





/* Defines for DMA_CH2 */
#define DMA_CH2_CHAN_ID                                                      (3)
#define UART_2_INST_DMA_TRIGGER                              (DMA_UART2_TX_TRIG)

/* Defines for DMA_CH1 */
#define DMA_CH1_CHAN_ID                                                      (2)
#define UART_1_INST_DMA_TRIGGER                              (DMA_UART3_TX_TRIG)

/* Defines for DMA_CH4 */
#define DMA_CH4_CHAN_ID                                                      (1)
#define UART_4_INST_DMA_TRIGGER                              (DMA_UART1_TX_TRIG)

/* Defines for DMA_CH3 */
#define DMA_CH3_CHAN_ID                                                      (0)
#define UART_3_INST_DMA_TRIGGER                              (DMA_UART0_TX_TRIG)



/* Defines for M1_D1: GPIOB.4 with pinCMx 17 on package pin 52 */
#define M1_M1_D1_PORT                                                    (GPIOB)
#define M1_M1_D1_PIN                                             (DL_GPIO_PIN_4)
#define M1_M1_D1_IOMUX                                           (IOMUX_PINCM17)
/* Defines for M1_D2: GPIOB.5 with pinCMx 18 on package pin 53 */
#define M1_M1_D2_PORT                                                    (GPIOB)
#define M1_M1_D2_PIN                                             (DL_GPIO_PIN_5)
#define M1_M1_D2_IOMUX                                           (IOMUX_PINCM18)
/* Defines for M1_CH1: GPIOA.9 with pinCMx 20 on package pin 55 */
#define M1_M1_CH1_PORT                                                   (GPIOA)
// pins affected by this interrupt request:["M1_CH1"]
#define M1_INT_IRQN                                             (GPIOA_INT_IRQn)
#define M1_INT_IIDX                             (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define M1_M1_CH1_IIDX                                       (DL_GPIO_IIDX_DIO9)
#define M1_M1_CH1_PIN                                            (DL_GPIO_PIN_9)
#define M1_M1_CH1_IOMUX                                          (IOMUX_PINCM20)
/* Defines for M1_CH2: GPIOA.8 with pinCMx 19 on package pin 54 */
#define M1_M1_CH2_PORT                                                   (GPIOA)
#define M1_M1_CH2_PIN                                            (DL_GPIO_PIN_8)
#define M1_M1_CH2_IOMUX                                          (IOMUX_PINCM19)
/* Defines for M2_D1: GPIOA.7 with pinCMx 14 on package pin 49 */
#define M2_M2_D1_PORT                                                    (GPIOA)
#define M2_M2_D1_PIN                                             (DL_GPIO_PIN_7)
#define M2_M2_D1_IOMUX                                           (IOMUX_PINCM14)
/* Defines for M2_D2: GPIOB.2 with pinCMx 15 on package pin 50 */
#define M2_M2_D2_PORT                                                    (GPIOB)
#define M2_M2_D2_PIN                                             (DL_GPIO_PIN_2)
#define M2_M2_D2_IOMUX                                           (IOMUX_PINCM15)
/* Defines for M2_CH1: GPIOB.0 with pinCMx 12 on package pin 47 */
#define M2_M2_CH1_PORT                                                   (GPIOB)
// groups represented: ["M3","M4","M2"]
// pins affected: ["M3_CH1","M4_CH1","M2_CH1"]
#define GPIO_MULTIPLE_GPIOB_INT_IRQN                            (GPIOB_INT_IRQn)
#define GPIO_MULTIPLE_GPIOB_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define M2_M2_CH1_IIDX                                       (DL_GPIO_IIDX_DIO0)
#define M2_M2_CH1_PIN                                            (DL_GPIO_PIN_0)
#define M2_M2_CH1_IOMUX                                          (IOMUX_PINCM12)
/* Defines for M2_CH2: GPIOB.1 with pinCMx 13 on package pin 48 */
#define M2_M2_CH2_PORT                                                   (GPIOB)
#define M2_M2_CH2_PIN                                            (DL_GPIO_PIN_1)
#define M2_M2_CH2_IOMUX                                          (IOMUX_PINCM13)
/* Defines for M3_D1: GPIOA.12 with pinCMx 34 on package pin 5 */
#define M3_M3_D1_PORT                                                    (GPIOA)
#define M3_M3_D1_PIN                                            (DL_GPIO_PIN_12)
#define M3_M3_D1_IOMUX                                           (IOMUX_PINCM34)
/* Defines for M3_D2: GPIOB.15 with pinCMx 32 on package pin 3 */
#define M3_M3_D2_PORT                                                    (GPIOB)
#define M3_M3_D2_PIN                                            (DL_GPIO_PIN_15)
#define M3_M3_D2_IOMUX                                           (IOMUX_PINCM32)
/* Defines for M3_CH1: GPIOB.16 with pinCMx 33 on package pin 4 */
#define M3_M3_CH1_PORT                                                   (GPIOB)
#define M3_M3_CH1_IIDX                                      (DL_GPIO_IIDX_DIO16)
#define M3_M3_CH1_PIN                                           (DL_GPIO_PIN_16)
#define M3_M3_CH1_IOMUX                                          (IOMUX_PINCM33)
/* Defines for M3_CH2: GPIOB.14 with pinCMx 31 on package pin 2 */
#define M3_M3_CH2_PORT                                                   (GPIOB)
#define M3_M3_CH2_PIN                                           (DL_GPIO_PIN_14)
#define M3_M3_CH2_IOMUX                                          (IOMUX_PINCM31)
/* Port definition for Pin Group M4 */
#define M4_PORT                                                          (GPIOB)

/* Defines for M4_D1: GPIOB.11 with pinCMx 28 on package pin 63 */
#define M4_M4_D1_PIN                                            (DL_GPIO_PIN_11)
#define M4_M4_D1_IOMUX                                           (IOMUX_PINCM28)
/* Defines for M4_D2: GPIOB.10 with pinCMx 27 on package pin 62 */
#define M4_M4_D2_PIN                                            (DL_GPIO_PIN_10)
#define M4_M4_D2_IOMUX                                           (IOMUX_PINCM27)
/* Defines for M4_CH1: GPIOB.7 with pinCMx 24 on package pin 59 */
#define M4_M4_CH1_IIDX                                       (DL_GPIO_IIDX_DIO7)
#define M4_M4_CH1_PIN                                            (DL_GPIO_PIN_7)
#define M4_M4_CH1_IOMUX                                          (IOMUX_PINCM24)
/* Defines for M4_CH2: GPIOB.6 with pinCMx 23 on package pin 58 */
#define M4_M4_CH2_PIN                                            (DL_GPIO_PIN_6)
#define M4_M4_CH2_IOMUX                                          (IOMUX_PINCM23)
/* Port definition for Pin Group IIC_GYR */
#define IIC_GYR_PORT                                                     (GPIOA)

/* Defines for SDA_GYR: GPIOA.0 with pinCMx 1 on package pin 33 */
#define IIC_GYR_SDA_GYR_PIN                                      (DL_GPIO_PIN_0)
#define IIC_GYR_SDA_GYR_IOMUX                                     (IOMUX_PINCM1)
/* Defines for SCL_GYR: GPIOA.1 with pinCMx 2 on package pin 34 */
#define IIC_GYR_SCL_GYR_PIN                                      (DL_GPIO_PIN_1)
#define IIC_GYR_SCL_GYR_IOMUX                                     (IOMUX_PINCM2)
/* Port definition for Pin Group IIC */
#define IIC_PORT                                                         (GPIOB)

/* Defines for IIC_SCL: GPIOB.19 with pinCMx 45 on package pin 16 */
#define IIC_IIC_SCL_PIN                                         (DL_GPIO_PIN_19)
#define IIC_IIC_SCL_IOMUX                                        (IOMUX_PINCM45)
/* Defines for IIC_SDA: GPIOB.20 with pinCMx 48 on package pin 19 */
#define IIC_IIC_SDA_PIN                                         (DL_GPIO_PIN_20)
#define IIC_IIC_SDA_IOMUX                                        (IOMUX_PINCM48)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_M_PWM_init(void);
void SYSCFG_DL_SERVO_init(void);
void SYSCFG_DL_TIMER_INT_init(void);
void SYSCFG_DL_I2C_init(void);
void SYSCFG_DL_UART_2_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_4_init(void);
void SYSCFG_DL_UART_3_init(void);
void SYSCFG_DL_DMA_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
