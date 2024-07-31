#ifndef __ARRAY_H__
#define __ARRAY_H__

int array_sum(unsigned len, const short array[len]);
unsigned array_find_min_index(unsigned len, const short array[len]);
unsigned array_find_max_index(unsigned len, const short array[len]);
void array_display(unsigned len, const short array[len]);

/// Return the length of the convolution array
unsigned convolve_unit(unsigned len, unsigned kernel_len, const short src[len],
                       short dest[len - kernel_len]);

unsigned forward_difference(unsigned len, const short src[len],
                            short dest[len - 1]);
#endif // !__ARRAY_H__
