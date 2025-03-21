#include "follow_line.h"
#include "User/device/cam.h"
#include "User/status/status.h"
#include "User/task/timed.h"


int16_t diff = 0;
Pid follow_line_pid;

void follow_line_pid_init(Pid *pid) {
  pid_init(pid, 1, 0, 0, 3, 20);

  return;
}

int16_t gw_8_getvalue(void) {
  int16_t buf = 0;
  uint8_t cnt = 0;
  uint8_t line = gw_gray_get_line_digital_is_black();

  for (int i = 0; i < 8; i++) {
    if (((line >> i) & 0x01)) {
      cnt++;
      buf += gw_bit_weight[i];
    }
  }
  if (cnt != 0) {
    return buf / cnt;
  } else {
    return 0;
  }
}

int16_t update_diff(enum GET_DIFF_WAYS way) {
  int16_t buf = 0;
  switch (way) {
  case GW_8:
    buf = gw_8_getvalue();
    break;
  case MS_3:
    buf = get_ms_diff() * 3;
    break;
  case CAM:
    buf = get_cam_diff();
  default:
    break;
  }
  return buf;
}

void follow_line(void *para) {
  int16_t speed_diff = 0;
  diff = update_diff(CAM); //修改巡线方式
  speed_diff = diff * 0.3;

  status.wheels[FONT_RIGHT].target = 500 - diff;
  status.wheels[FONT_LEFT].target = 500 + diff;

  Task T = task_new(follow_line, para);
  task_timed_insert(&task.timed, T, (uint32_t)para & 0xff);

  return;
}

void start_follow_line(uint8_t time) //time*50ms巡线一次
{

    uint32_t para = time;

    follow_line((void *)para);

    return;
}

