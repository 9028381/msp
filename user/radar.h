/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-06 20:47:56
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-06 20:52:05
 * @FilePath: \empty\user\radar.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef RADAR_H_
#define RADAR_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "empty/ti_msp_dl_config.h"
#include "string.h"

#define HEADER_0 0xA5
#define HEADER_1 0x5A
#define Length_ 0x6C

#define POINT_PER_PACK 32

typedef struct PointData {
  uint8_t distance_h;
  uint8_t distance_l;
  uint8_t Strong;

} LidarPointStructDef;

typedef struct PackData {
  uint8_t header_0;
  uint8_t header_1;
  uint8_t ver_len;

  uint8_t speed_h;
  uint8_t speed_l;
  uint8_t start_angle_h;
  uint8_t start_angle_l;
  LidarPointStructDef point[POINT_PER_PACK];
  uint8_t end_angle_h;
  uint8_t end_angle_l;
  uint8_t crc;
} LiDARFrameTypeDef;

typedef struct PointDataProcess_ {
  uint16_t distance;
  float angle;
} PointDataProcessDef;

void data_process(void);
float float_abs(float input);

extern PointDataProcessDef PointDataProcess[1200];
extern PointDataProcessDef Dataprocess[1200];
extern LiDARFrameTypeDef Pack_Data;
extern int data_cnt, data_error_cnt;
extern int data_flag, data_process_flag;

extern void Ladar_drive(uint8_t temp_data); //雷达驱动函数，放在中断中
extern void radar_data_process(); //雷达数据处理函数，放在while（1）中

extern uint16_t radar_data[360];
#endif
