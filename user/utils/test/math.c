#include "../math.h"
#include <stdio.h>

void show_const() {
  printf("PI = %f\n", PI);
  printf("E  = %f\n", E);
}

void test_limit() {
  printf("LIMIT_MAX(1, 2) = %d\n", LIMIT_MAX(1, 2));
  printf("LIMIT_MAX(3, 2) = %d\n", LIMIT_MAX(3, 2));
  printf("LIMIT_MAX(1, 3) = %d\n", LIMIT_MAX(1, 3));
  printf("LIMIT_MIN(1, 2) = %d\n", LIMIT_MIN(1, 2));
  printf("LIMIT_MIN(3, 2) = %d\n", LIMIT_MIN(3, 2));
  printf("LIMIT_MIN(1, 3) = %d\n", LIMIT_MIN(1, 3));
  printf("LIMIT(1, 2, 3) = %d\n", LIMIT(1, 2, 3));
  printf("LIMIT(3, 2, 3) = %d\n", LIMIT(3, 2, 3));
  printf("CLAMP(1, 2) = %d\n", CLAMP(1, 2));
  printf("CLAMP(3, 2) = %d\n", CLAMP(3, 2));
  printf("CLAMP(1, 3) = %d\n", CLAMP(1, 3));
  printf("CLAMP(-1, 2) = %d\n", CLAMP(-1, 2));
  printf("CLAMP(-4, 2) = %d\n", CLAMP(-4, 2));
}

int main(int argc, char *argv[]) {
  show_const();
  test_limit();
}
