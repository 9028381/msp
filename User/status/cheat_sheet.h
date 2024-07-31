#ifndef __CHEAT_SHEET_H__
#define __CHEAT_SHEET_H__

struct DistanceTraveled {
  int min;
  int max;
};

struct CheatSheet {
  struct DistanceTraveled AtoB;
};

struct CheatSheet cheat_sheet_default();

#endif // !__CHEAT_SHEET_H__
