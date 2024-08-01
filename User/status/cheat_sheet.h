#ifndef __CHEAT_SHEET_H__
#define __CHEAT_SHEET_H__

#include "stdint.h"

struct RangeMinMax {
  int min;
  int max;
};

struct LeftRight {
  int left;
  int right;
};

#define SPEED_LEVELS 3

enum SpeedLevel {
  SpeedSlow = 0,
  SpeedNorm = 1,
  SpeedFast = 2,
};

struct CheatSheet {
  struct RangeMinMax AtoB;
  struct LeftRight turn_speed[SPEED_LEVELS];
  int forward_speed[SPEED_LEVELS];
  int arc_continue1;
  int arc_continue2;
  int forward1;
  int forward2;
  int arc_start;
  struct RangeMinMax arc_enter1;
  struct RangeMinMax arc_enter2;
};

struct CheatSheet cheat_sheet_default();
void cheat_sheet_rpc_recover(uint16_t var, void *p);

#endif // !__CHEAT_SHEET_H__
