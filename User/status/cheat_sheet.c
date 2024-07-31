#include "cheat_sheet.h"

struct CheatSheet cheat_sheet_default() {
  struct CheatSheet ret;

  // answer 1 A -> B
  // answer 2 A -> B and C -> D
  ret.AtoB.min = 0;
  ret.AtoB.max = 0;

  return ret;
}
