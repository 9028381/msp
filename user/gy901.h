/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-04 12:43:49
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-04 12:44:10
 * @FilePath: \empty\user\gy901.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__

#include "C:/ti/mspm0_sdk_2_01_00_03/examples/nortos/LP_MSPM0G3507/driverlib/empty/ti_msp_dl_config.h"

enum gyroscope
{
    gyr_a_x = 0x34,     // Acceleration of the sensor along the x-axis
    gyr_a_y = 0x35,     // Acceleration of the sensor along the y-axis
    gyr_a_z = 0x36,     // Acceleration of the sensor along the z-axis
    gyr_w_x = 0x37,     // The angular velocity of the sensor around the x-axis
    gyr_w_y = 0x38,     // The angular velocity of the sensor around the y-axis
    gyr_w_z = 0x39,     // The angular velocity of the sensor around the z-axis
    gyr_x_roll = 0x3D,  // The angle of the sensor around the x-axis
    gyr_y_pitch = 0x3E, // The angle of the sensor around the y-axis
    gyr_z_yaw = 0x3F,   // The angle of the sensor around the z-axis
};

float Get_gyr_value(enum gyroscope key);

#endif /* !__GYROSCOPE_H__ */
