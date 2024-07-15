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

int16_t get_cam_diff(void) { return cam_diff ; }
