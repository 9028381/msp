#include "cheat_sheet.h"

struct CheatSheet cheat_sheet_default() {
  struct CheatSheet ret;

  // answer 1 A -> B
  // answer 2 A -> B and C -> D
  // 125, 129, 128, 126
  ret.AtoB.min = 125000;
  ret.AtoB.max = 132000;

  // forward speed
  ret.forward_speed[SpeedSlow] = 200;
  ret.forward_speed[SpeedNorm] = 400;
  ret.forward_speed[SpeedFast] = 600;

  // turn speed
  ret.turn_speed[SpeedSlow].left = 200;
  ret.turn_speed[SpeedSlow].right = 144;
  ret.turn_speed[SpeedNorm].left = 500;
  ret.turn_speed[SpeedNorm].right = 360;
  ret.turn_speed[SpeedFast].left = 0;
  ret.turn_speed[SpeedFast].right = 0;

  return ret;
}
