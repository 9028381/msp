#include "status.h"

struct Status status;

void status_init(struct Status *status) {
  // time init
  status->times = 0;

  // sensor init

  // wheels init
  status_wheels_init(status->wheels);

  // mode init
  status->mode.turn = false;
  status->mode.follow = false;
}

void status_next(struct Status *status) {
  // time next
  status->times++;

  // sensor next

  // update wheels
  status_wheels_next(status->wheels);

  // wheels drive
  status_wheels_drive(status->wheels);

  // mode next
}
