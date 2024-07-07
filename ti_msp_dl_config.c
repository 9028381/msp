/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_UART_Main_backupConfig gUART_1Backup;
DL_TimerA_backupConfig gM_PWMBackup;
DL_TimerG_backupConfig gSERVOBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_UART_2_init();
    SYSCFG_DL_UART_1_init();
    SYSCFG_DL_UART_4_init();
    SYSCFG_DL_UART_3_init();
    SYSCFG_DL_TIMER_INT_init();
    SYSCFG_DL_I2C_init();
    SYSCFG_DL_M_PWM_init();
    SYSCFG_DL_SERVO_init();
    SYSCFG_DL_DMA_init();
    /* Ensure backup structures have no valid state */
	gUART_1Backup.backupRdy 	= false;

	gM_PWMBackup.backupRdy 	= false;
	gSERVOBackup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_UART_Main_saveConfiguration(UART_1_INST, &gUART_1Backup);
	retStatus &= DL_TimerA_saveConfiguration(M_PWM_INST, &gM_PWMBackup);
	retStatus &= DL_TimerG_saveConfiguration(SERVO_INST, &gSERVOBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_UART_Main_restoreConfiguration(UART_1_INST, &gUART_1Backup);
	retStatus &= DL_TimerA_restoreConfiguration(M_PWM_INST, &gM_PWMBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(SERVO_INST, &gSERVOBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_UART_Main_reset(UART_2_INST);
    DL_UART_Main_reset(UART_1_INST);
    DL_UART_Main_reset(UART_4_INST);
    DL_UART_Main_reset(UART_3_INST);
    DL_TimerG_reset(TIMER_INT_INST);
    DL_I2C_reset(I2C_INST);
    DL_TimerA_reset(M_PWM_INST);
    DL_TimerG_reset(SERVO_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_UART_Main_enablePower(UART_2_INST);
    DL_UART_Main_enablePower(UART_1_INST);
    DL_UART_Main_enablePower(UART_4_INST);
    DL_UART_Main_enablePower(UART_3_INST);
    DL_TimerG_enablePower(TIMER_INT_INST);
    DL_I2C_enablePower(I2C_INST);
    DL_TimerA_enablePower(M_PWM_INST);
    DL_TimerG_enablePower(SERVO_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_2_IOMUX_TX, GPIO_UART_2_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_2_IOMUX_RX, GPIO_UART_2_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_1_IOMUX_TX, GPIO_UART_1_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_1_IOMUX_RX, GPIO_UART_1_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_4_IOMUX_TX, GPIO_UART_4_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_4_IOMUX_RX, GPIO_UART_4_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_3_IOMUX_TX, GPIO_UART_3_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_3_IOMUX_RX, GPIO_UART_3_IOMUX_RX_FUNC);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_IOMUX_SDA,
        GPIO_I2C_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_IOMUX_SCL,
        GPIO_I2C_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(GPIO_M_PWM_C0_IOMUX,GPIO_M_PWM_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_M_PWM_C0_PORT, GPIO_M_PWM_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_M_PWM_C1_IOMUX,GPIO_M_PWM_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_M_PWM_C1_PORT, GPIO_M_PWM_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_M_PWM_C2_IOMUX,GPIO_M_PWM_C2_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_M_PWM_C2_PORT, GPIO_M_PWM_C2_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_M_PWM_C3_IOMUX,GPIO_M_PWM_C3_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_M_PWM_C3_PORT, GPIO_M_PWM_C3_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_SERVO_C0_IOMUX,GPIO_SERVO_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_SERVO_C0_PORT, GPIO_SERVO_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_SERVO_C1_IOMUX,GPIO_SERVO_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_SERVO_C1_PORT, GPIO_SERVO_C1_PIN);

    DL_GPIO_initDigitalOutput(M1_M1_D1_IOMUX);

    DL_GPIO_initDigitalOutput(M1_M1_D2_IOMUX);

    DL_GPIO_initDigitalInput(M1_M1_CH1_IOMUX);

    DL_GPIO_initDigitalInput(M1_M1_CH2_IOMUX);

    DL_GPIO_initDigitalOutput(M2_M2_D1_IOMUX);

    DL_GPIO_initDigitalOutput(M2_M2_D2_IOMUX);

    DL_GPIO_initDigitalInput(M2_M2_CH1_IOMUX);

    DL_GPIO_initDigitalInput(M2_M2_CH2_IOMUX);

    DL_GPIO_initDigitalOutput(M3_M3_D1_IOMUX);

    DL_GPIO_initDigitalOutput(M3_M3_D2_IOMUX);

    DL_GPIO_initDigitalInput(M3_M3_CH1_IOMUX);

    DL_GPIO_initDigitalInput(M3_M3_CH2_IOMUX);

    DL_GPIO_initDigitalOutput(M4_M4_D1_IOMUX);

    DL_GPIO_initDigitalOutput(M4_M4_D2_IOMUX);

    DL_GPIO_initDigitalInput(M4_M4_CH1_IOMUX);

    DL_GPIO_initDigitalInput(M4_M4_CH2_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_GYR_SDA_GYR_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_GYR_SCL_GYR_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_IIC_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_IIC_SDA_IOMUX);

    DL_GPIO_clearPins(GPIOA, M2_M2_D1_PIN |
		M3_M3_D1_PIN |
		IIC_GYR_SDA_GYR_PIN |
		IIC_GYR_SCL_GYR_PIN);
    DL_GPIO_enableOutput(GPIOA, M2_M2_D1_PIN |
		M3_M3_D1_PIN |
		IIC_GYR_SDA_GYR_PIN |
		IIC_GYR_SCL_GYR_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_9_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, M1_M1_CH1_PIN);
    DL_GPIO_enableInterrupt(GPIOA, M1_M1_CH1_PIN);
    DL_GPIO_clearPins(GPIOB, M1_M1_D1_PIN |
		M1_M1_D2_PIN |
		M2_M2_D2_PIN |
		M3_M3_D2_PIN |
		M4_M4_D1_PIN |
		M4_M4_D2_PIN |
		IIC_IIC_SCL_PIN |
		IIC_IIC_SDA_PIN);
    DL_GPIO_enableOutput(GPIOB, M1_M1_D1_PIN |
		M1_M1_D2_PIN |
		M2_M2_D2_PIN |
		M3_M3_D2_PIN |
		M4_M4_D1_PIN |
		M4_M4_D2_PIN |
		IIC_IIC_SCL_PIN |
		IIC_IIC_SDA_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOB, DL_GPIO_PIN_0_EDGE_RISE |
		DL_GPIO_PIN_7_EDGE_RISE);
    DL_GPIO_setUpperPinsPolarity(GPIOB, DL_GPIO_PIN_16_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOB, M2_M2_CH1_PIN |
		M3_M3_CH1_PIN |
		M4_M4_CH1_PIN);
    DL_GPIO_enableInterrupt(GPIOB, M2_M2_CH1_PIN |
		M3_M3_CH1_PIN |
		M4_M4_CH1_PIN);

}


SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    /* Set default configuration */
    DL_SYSCTL_disableHFXT();
    DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_1);
    DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIVIDER_DISABLE);
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOB_INT_IRQn, 0);

}



static const DL_UART_Main_ClockConfig gUART_2ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_2Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_2_init(void)
{
    DL_UART_Main_setClockConfig(UART_2_INST, (DL_UART_Main_ClockConfig *) &gUART_2ClockConfig);

    DL_UART_Main_init(UART_2_INST, (DL_UART_Main_Config *) &gUART_2Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 460800
     *  Actual baud rate: 460431.65
     */
    DL_UART_Main_setOversampling(UART_2_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_2_INST, UART_2_IBRD_32_MHZ_460800_BAUD, UART_2_FBRD_32_MHZ_460800_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_2_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART_2_INST_INT_IRQN, 3);

    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(UART_2_INST);

    DL_UART_Main_enable(UART_2_INST);
}

static const DL_UART_Main_ClockConfig gUART_1ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_1Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_1_init(void)
{
    DL_UART_Main_setClockConfig(UART_1_INST, (DL_UART_Main_ClockConfig *) &gUART_1ClockConfig);

    DL_UART_Main_init(UART_1_INST, (DL_UART_Main_Config *) &gUART_1Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_1_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_1_INST, UART_1_IBRD_32_MHZ_115200_BAUD, UART_1_FBRD_32_MHZ_115200_BAUD);


    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(UART_1_INST);

    DL_UART_Main_enable(UART_1_INST);
}

static const DL_UART_Main_ClockConfig gUART_4ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_4Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_4_init(void)
{
    DL_UART_Main_setClockConfig(UART_4_INST, (DL_UART_Main_ClockConfig *) &gUART_4ClockConfig);

    DL_UART_Main_init(UART_4_INST, (DL_UART_Main_Config *) &gUART_4Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.24
     */
    DL_UART_Main_setOversampling(UART_4_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_4_INST, UART_4_IBRD_32_MHZ_9600_BAUD, UART_4_FBRD_32_MHZ_9600_BAUD);


    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(UART_4_INST);

    DL_UART_Main_enable(UART_4_INST);
}

static const DL_UART_Main_ClockConfig gUART_3ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_3Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_3_init(void)
{
    DL_UART_Main_setClockConfig(UART_3_INST, (DL_UART_Main_ClockConfig *) &gUART_3ClockConfig);

    DL_UART_Main_init(UART_3_INST, (DL_UART_Main_Config *) &gUART_3Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 460800
     *  Actual baud rate: 460431.65
     */
    DL_UART_Main_setOversampling(UART_3_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_3_INST, UART_3_IBRD_32_MHZ_460800_BAUD, UART_3_FBRD_32_MHZ_460800_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_3_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART_3_INST_INT_IRQN, 3);

    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(UART_3_INST);

    DL_UART_Main_enable(UART_3_INST);
}


/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   125000 Hz = 32000000 Hz / (1 * (255 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_INTClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 255U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_INT_INST_LOAD_VALUE = (50ms * 125000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_INTTimerConfig = {
    .period     = TIMER_INT_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_INT_init(void) {

    DL_TimerG_setClockConfig(TIMER_INT_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_INTClockConfig);

    DL_TimerG_initTimerMode(TIMER_INT_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_INTTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_INT_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_INT_INST_INT_IRQN, 2);
    DL_TimerG_enableClock(TIMER_INT_INST);





}


static const DL_I2C_ClockConfig gI2CClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_init(void) {

    DL_I2C_setClockConfig(I2C_INST,
        (DL_I2C_ClockConfig *) &gI2CClockConfig);
    DL_I2C_disableAnalogGlitchFilter(I2C_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_INST);
    /* Set frequency to 100000 Hz*/
    DL_I2C_setTimerPeriod(I2C_INST, 31);
    DL_I2C_setControllerTXFIFOThreshold(I2C_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(I2C_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_INST);


    /* Enable module */
    DL_I2C_enableController(I2C_INST);


}

/*
 * Timer clock configuration to be sourced by  / 1 (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gM_PWMClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gM_PWMConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 10000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_M_PWM_init(void) {

    DL_TimerA_setClockConfig(
        M_PWM_INST, (DL_TimerA_ClockConfig *) &gM_PWMClockConfig);

    DL_TimerA_initPWMMode(
        M_PWM_INST, (DL_TimerA_PWMConfig *) &gM_PWMConfig);

    DL_TimerA_setCaptureCompareOutCtl(M_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(M_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);
    DL_TimerA_setCaptureCompareValue(M_PWM_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(M_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(M_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(M_PWM_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(M_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_2_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(M_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_2_INDEX);
    DL_TimerA_setCaptureCompareValue(M_PWM_INST, 0, DL_TIMER_CC_2_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(M_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_3_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(M_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_3_INDEX);
    DL_TimerA_setCaptureCompareValue(M_PWM_INST, 0, DL_TIMER_CC_3_INDEX);

    DL_TimerA_enableClock(M_PWM_INST);


    
    DL_TimerA_setCCPDirection(M_PWM_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT | DL_TIMER_CC2_OUTPUT | DL_TIMER_CC3_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   160000 Hz = 4000000 Hz / (8 * (24 + 1))
 */
static const DL_TimerG_ClockConfig gSERVOClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 24U
};

static const DL_TimerG_PWMConfig gSERVOConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 3200,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_SERVO_init(void) {

    DL_TimerG_setClockConfig(
        SERVO_INST, (DL_TimerG_ClockConfig *) &gSERVOClockConfig);

    DL_TimerG_initPWMMode(
        SERVO_INST, (DL_TimerG_PWMConfig *) &gSERVOConfig);

    DL_TimerG_setCaptureCompareOutCtl(SERVO_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(SERVO_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(SERVO_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptureCompareOutCtl(SERVO_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(SERVO_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(SERVO_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(SERVO_INST);


    
    DL_TimerG_setCCPDirection(SERVO_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}


static const DL_DMA_Config gDMA_CH2Config = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = UART_2_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_CH2_init(void)
{
    DL_DMA_initChannel(DMA, DMA_CH2_CHAN_ID , (DL_DMA_Config *) &gDMA_CH2Config);
}
static const DL_DMA_Config gDMA_CH1Config = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = UART_1_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_CH1_init(void)
{
    DL_DMA_initChannel(DMA, DMA_CH1_CHAN_ID , (DL_DMA_Config *) &gDMA_CH1Config);
}
static const DL_DMA_Config gDMA_CH4Config = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = UART_4_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_CH4_init(void)
{
    DL_DMA_initChannel(DMA, DMA_CH4_CHAN_ID , (DL_DMA_Config *) &gDMA_CH4Config);
}
static const DL_DMA_Config gDMA_CH3Config = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = UART_3_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_CH3_init(void)
{
    DL_DMA_initChannel(DMA, DMA_CH3_CHAN_ID , (DL_DMA_Config *) &gDMA_CH3Config);
}
SYSCONFIG_WEAK void SYSCFG_DL_DMA_init(void){
    SYSCFG_DL_DMA_CH2_init();
    SYSCFG_DL_DMA_CH1_init();
    SYSCFG_DL_DMA_CH4_init();
    SYSCFG_DL_DMA_CH3_init();
}


