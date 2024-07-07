#include "status.h"
#include "rpc.h"

struct Status status;

void status_init(struct Status *status) {
  status->times = 0;
  status_rpc_init(status->rpc);
  // sensor init
  status_wheels_init(status->wheels);
}

void status_next(struct Status *status) {
  status->times++;
  // sensor next
  status_wheels_next(status->wheels);
}

void status_drive(struct Status *status) {
  status_wheels_drive(status->wheels);
}
