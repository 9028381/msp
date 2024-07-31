#include "Debug/ti_msp_dl_config.h"
#include "User/drive/delay.h"
#include "User/utils/array.h"
#include "User/utils/log.h"
#include "User/utils/utils.h"
#include "ti/driverlib/dl_adc12.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/m0p/dl_core.h"

short CCD_DATA[128] = {0};

#define CCD_ARRAY &CCD_DATA[15]
#define CCD_ARRAY_LEN (128 - 15 * 2)
/* #define CCD_KERNEL_LEN 20 */
#define CCD_BLACK_THRUST 400
#define CCD_COUNT_THRUST 5

short get_adc_val(void) {
  DL_ADC12_startConversion(ADC12_0_INST);

  delay_us(2);

  unsigned gADCResult = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);

  DL_ADC12_enableConversions(ADC12_0_INST);

  return gADCResult >> 1;
}

void start_ccd(void) {
  DL_GPIO_clearPins(CCD_CLK_PORT, CCD_CLK_PIN);
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

void get_ccd(void) {
  for (int i = 0; i < 128; i++) {
    DL_GPIO_clearPins(CCD_CLK_PORT, CCD_CLK_PIN);
    delay_us(1); // 曝光时间
    CCD_DATA[i] = get_adc_val();
    DL_GPIO_writePins(CCD_CLK_PORT, CCD_CLK_PIN);
    delay_us(1);
  }
}

void get_ccd_val(void) {
  start_ccd();
  get_ccd();
  /* INFO("CCD_DATA"); */
  // array_display(CCD_ARRAY_LEN, CCD_ARRAY);

  return;
}

int ccd_compute() {
  get_ccd_val();
  short dest[128];
  /* int len = convolve_unit(CCD_ARRAY_LEN, CCD_KERNEL_LEN, CCD_ARRAY, dest); */
  /* int len = forward_difference_multiple(128 - 15, 6, &CCD_DATA[15], dest); */
  struct SumAndCount sum_count =
      array_mean_index_less_than(CCD_ARRAY_LEN, CCD_ARRAY, CCD_BLACK_THRUST);
  /* array_display(len, dest); */

  if (sum_count.count < CCD_COUNT_THRUST) {
    INFO("CCD not found black.");
    return ROAD_NO;
  }

  int diff = sum_count.sum / sum_count.count - CCD_ARRAY_LEN / 2;
  INFO("CCD fond black: %d", diff);

  return diff;
}
