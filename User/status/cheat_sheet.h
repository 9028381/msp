#ifndef __CHEAT_SHEET_H__
#define __CHEAT_SHEET_H__

struct MinMax {
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
  struct MinMax AtoB;
  struct LeftRight turn_speed[SPEED_LEVELS];
  int forward_speed[SPEED_LEVELS];
};

struct CheatSheet cheat_sheet_default();

#endif // !__CHEAT_SHEET_H__
