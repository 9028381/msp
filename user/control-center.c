/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-04 17:11:18
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-04 18:01:03
 * @FilePath: \empty\user\control-center.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "C:/ti/mspm0_sdk_2_01_00_03/examples/nortos/LP_MSPM0G3507/driverlib/empty/ti_msp_dl_config.h"
#include <stdint.h>

int32_t M_F_L_cur = 0;
int32_t M_F_R_cur = 0;
int32_t M_B_L_cur = 0;
int32_t M_B_R_cur = 0;

int32_t M_F_L_tar = 0;
int32_t M_F_R_tar = 0;
int32_t M_B_L_tar = 0;
int32_t M_B_R_tar = 0;
