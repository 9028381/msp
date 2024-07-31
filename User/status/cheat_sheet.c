#include "cheat_sheet.h"

struct CheatSheet cheat_sheet_default() {
  struct CheatSheet ret;

  // answer 1 A -> B
  // answer 2 A -> B and C -> D
  ret.AtoB.min = 0;
  ret.AtoB.max = 0;

  // forward speed
  ret.forward_speed[SpeedSlow] = 200;
  ret.forward_speed[SpeedNorm] = 400;
  ret.forward_speed[SpeedFast] = 600;

  // turn speed
  ret.turn_speed[SpeedSlow].left = 0;
  ret.turn_speed[SpeedSlow].right = 0;
  ret.turn_speed[SpeedNorm].left = 0;
  ret.turn_speed[SpeedNorm].right = 0;
  ret.turn_speed[SpeedFast].left = 0;
  ret.turn_speed[SpeedFast].right = 0;

  return ret;
}
