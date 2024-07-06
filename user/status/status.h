#ifndef __STATUS_H__
#define __STATUS_H__

#include "../config.h"

struct Status {
  /// times / STATUS_FREQ == run time(s)
  unsigned int times;
};

extern struct Status status;

void status_init();
void status_next();

#endif // !__STATUS_H__
