#include "ms_gray.h"

int16_t ms_diff = 0;
char rx_buf[8] = {0};

void update_ms_diff(uint8_t buf) {
  static unsigned char index = 0;
  if (buf == '\n') {
    rx_buf[index] = '\0';
    ms_diff = atoi(rx_buf);
    index = 0;
  } else {
    rx_buf[index++] = buf;
  }
}

int16_t get_ms_diff(void) { return -ms_diff / 10; }
