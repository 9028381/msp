#include "ti/driverlib/dl_adc12.h"
#include "User/utils/log.h"
#include "Debug/ti_msp_dl_config.h"
#include "User/drive/delay.h"
#include "ti/driverlib/dl_gpio.h"
#include "User/utils/array.h"
#include "ti/driverlib/m0p/dl_core.h"

uint16_t CCD_DATA[128] = {0};
uint16_t gADCResult = 0;

uint16_t get_adc_val(void)
{
    DL_ADC12_startConversion(ADC12_0_INST);

    delay_us(2);

    gADCResult = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);

    DL_ADC12_enableConversions(ADC12_0_INST);

    return gADCResult;
}

void start_ccd(void)
{
    DL_GPIO_clearPins(CCD_CLK_PORT ,CCD_CLK_PIN);
    DL_GPIO_clearPins(CCD_SI_PORT, CCD_SI_PIN);
    delay_us(20);

    DL_GPIO_clearPins(CCD_CLK_PORT, CCD_CLK_PIN);
    DL_GPIO_writePins(CCD_SI_PORT, CCD_SI_PIN);
    delay_us(20);

    DL_GPIO_writePins(CCD_CLK_PORT, CCD_CLK_PIN);
    delay_us(20);
    DL_GPIO_clearPins(CCD_SI_PORT, CCD_SI_PIN);

    delay_us(20);

    return;
}

void get_ccd(void)
{
    for(int i = 0; i < 128; i++)
    {
        DL_GPIO_clearPins(CCD_CLK_PORT, CCD_CLK_PIN);
        delay_us(20); // 曝光时间
        CCD_DATA[i] = get_adc_val();
        DL_GPIO_writePins(CCD_CLK_PORT, CCD_CLK_PIN);
        delay_us(1);
    }
}

void get_ccd_val(void)
{
    start_ccd();
    get_ccd();
    INFO("");
    array_display(128, CCD_DATA);


    return;
}