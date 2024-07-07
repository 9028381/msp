#include "../rpc.h"
#include <stdio.h>
#include <stdlib.h>

struct Status {
  RPC rpc;
};

int main(int argc, char *argv[]) {
  printf("RPC size = %zd\n", sizeof(RPC));
  return EXIT_SUCCESS;
}
