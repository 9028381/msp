#include "array.h"
#include "log.h"

int array_sum(unsigned len, const short array[len]) {
  int sum = 0;
  for (unsigned int i = 0; i < len; i++)
    sum += array[i];
  return sum;
}

unsigned array_find_min_index(unsigned len, const short array[len]) {
  unsigned min_index = 0;
  short min = array[min_index];
  for (unsigned i = 1; i < len; i++)
    if (array[i] < min) {
      min = array[i];
      min_index = i;
    }

  return min_index;
}

unsigned array_find_max_index(unsigned len, const short array[len]) {
  unsigned max_index = 0;
  short max = array[max_index];
  for (unsigned i = 1; i < len; i++)
    if (array[i] > max) {
      max = array[i];
      max_index = i;
    }

  return max_index;
}

void array_display(unsigned len, const short array[len]) {
  PRINTF("[");
  for (unsigned int i = 0; i < len - 1; i++)
    PRINTF("%hd, ", array[i]);
  PRINTLN("%hd]", array[len - 1]);
}

#ifdef __ARRAY_FIND_MIN_INDEX__

#include <stdio.h>

void array_display(unsigned len, const unsigned short array[len]) {
  putchar('[');
  for (unsigned int i = 0; i < len - 1; i++)
    printf("%d, ", array[i]);
  printf("%d", array[len - 1]);
  putchar(']');
  putchar('\n');
}

void test1() {
  unsigned short array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  array_display(10, array);
  printf("%u\n", array_find_min_index(10, array));
}

void test2() {
  unsigned short array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  array_display(10, array);
  printf("%u\n", array_find_min_index(10, array));
}

void test3() {
  unsigned short array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  array_display(10, array);
  printf("%u\n", array_find_min_index(10, array));
}

void test4() {
  unsigned short array[] = {8, 8, 3, 2, 4, 6, 1, 6, 48, 8};
  array_display(10, array);
  printf("%u\n", array_find_min_index(10, array));
}

int main() {
  test1();
  test2();
  test3();
  test4();
}

#endif /* ifdef __ARRAY_FIND_MIN_INDEX__ */
