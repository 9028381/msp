#include "status.h"

struct Status status;

void status_init() { status.times = 0; }

void status_next() { status.times++; }
