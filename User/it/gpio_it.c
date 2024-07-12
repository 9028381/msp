#include "gpio_it.h"
#include "User/drive/motor.h"
#include "ti_msp_dl_config.h"

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

void enable_all_gpio_it(void) {
  NVIC_EnableIRQ(GPIOA_INT_IRQn);
  NVIC_EnableIRQ(GPIOB_INT_IRQn);
}
