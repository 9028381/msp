#include "array.h"

unsigned forward_difference(unsigned len, const short src[len],
                            short dest[len - 1]) {
  if (len == 0)
    return 0;

  for (unsigned i = 0; i < len - 1; i++)
    dest[i] = src[i + 1] - src[i];

  return len - 1;
}
