#include "../log.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  for (unsigned int times = 0; times <= 10000; times++)
    printf(LOG_TIME_FMT_TYPE "\n", LOG_TIME_FMT(times));
  return EXIT_SUCCESS;
}
