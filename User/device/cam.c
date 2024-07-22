#include "cam.h"

int16_t cam_diff = 0;
char cam_rx_buf[8] = {0};

void update_cam_diff(uint8_t buf) {
  static unsigned char index = 0;
  if (buf == '\n') {
    cam_rx_buf[index] = '\0';
    cam_diff = atoi(cam_rx_buf);
    index = 0;
  } else {
    cam_rx_buf[index++] = buf;
  }
}

int16_t get_cam_diff(void)
{
    switch (cam_diff)
    {
        case Left_road: return -20000;
        case Right_road: return 20000;
        case T_R_road: return 0;
        case T_L_road: return 0;
        case T_B_road: status.base_speed = 0; return 0;
        case CROSS_road: return 0;
        default: return cam_diff;
    }
}
