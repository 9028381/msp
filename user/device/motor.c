#include "motor.h"
#include "../encounter.h"

int motor_get_speed(enum WheelPosition which) {
  int speed;
  switch (which) {
  case FONT_LEFT:
    speed = L_1 - 0xefff;
    L_1 = 0xefff;
    break;
  case FONT_RIGHT:
    speed = L_2 - 0xefff;
    L_2 = 0xefff;
    break;
  case BACK_LEFT:
    speed = L_3 - 0xefff;
    L_3 = 0xefff;
    break;
  case BACK_RIGHT:
    speed = L_4 - 0xefff;
    L_4 = 0xefff;
    break;
  }
  return speed;
}
