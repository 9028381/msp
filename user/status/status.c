#include "status.h"
#include "wheel.h"

struct Status status;

void status_init(struct Status *status) {
  status->times = 0;
  // sensor init
  status_wheels_init(status->wheels);
}

void status_next(struct Status *status) {
  status->times++;
  // sensor next
  status_wheels_next(status->wheels);
}
