#include "cheat_sheet.h"
#include "status.h"

struct CheatSheet cheat_sheet_default() {
  struct CheatSheet ret;

  // answer 1 A -> B
  // answer 2 A -> B and C -> D
  // 125, 129, 128, 126
  ret.AtoB.min = 125000;
  ret.AtoB.max = 132000;

  // forward speed
  ret.forward_speed[SpeedSlow] = 200;
  ret.forward_speed[SpeedNorm] = 500;
  ret.forward_speed[SpeedFast] = 800;

  // turn speed
  ret.turn_speed[SpeedSlow].left = 200;
  ret.turn_speed[SpeedSlow].right = 144;
  ret.turn_speed[SpeedNorm].left = 500;
  ret.turn_speed[SpeedNorm].right = 356;
  ret.turn_speed[SpeedFast].left = 600;
  ret.turn_speed[SpeedFast].right = 432;

  ret.arc_continue1 = 52000;
  ret.arc_continue2 = 52000;
  ret.forward1 = 78000;
  ret.forward2 = 78000;
  ret.arc_enter1.min  = 42000;
  ret.arc_enter1.max  = 45000;
  ret.arc_enter2.min  = 42000;
  ret.arc_enter2.max  = 45000;

  return ret;
}

void cheat_sheet_rpc_recover(uint16_t var, void *p){
  status.cheat_sheet = cheat_sheet_default();
}
