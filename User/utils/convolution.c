#include "array.h"

unsigned convolve_unit(unsigned char len, unsigned char kernel_len,
                       const unsigned short src[len],
                       unsigned short dest[len - kernel_len + 1]) {
  if (len == 0)
    return 0;

  if (kernel_len == 0) {
    for (unsigned i = 0; i < len; i++)
      dest[i] = 0;
    return len;
  }

  if (kernel_len >= len) {
    dest[0] = array_sum(len, src);
    return 1;
  }

  unsigned part = array_sum(kernel_len, src);
  unsigned remain = len - kernel_len;
  dest[0] = part;
  for (unsigned i = 0; i < remain; i++) {
    part -= src[i];
    part += src[i + kernel_len];
    dest[i + 1] = part;
  }
  return len - kernel_len + 1;
}

#ifdef __CONVOLUTION_TEST__
#include "stdio.h"

int main(int argc, char *argv[]) {
  unsigned short array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unsigned short dest[10];
  unsigned ret = 0;

  for (int test = 0; test < 11; test++) {
    printf("\n");
    for (int i = 0; i < 10; i++)
      printf("%d ", array[i]);
    printf("\n");
    ret = convolve_unit(10, test, array, dest);
    for (int i = 0; i < 10; i++)
      printf("%d ", dest[i]);
    printf("return:%u\n", ret);
    for (int i = 0; i < 10; i++)
      dest[i] = 0;
  }
}
#endif // __CONVOLUTION_TEST__
