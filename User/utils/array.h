#ifndef __ARRAY_H__
#define __ARRAY_H__

unsigned array_sum(unsigned len, const unsigned short array[len]);
unsigned array_find_min_index(unsigned len, const unsigned short array[len]);
void array_display(unsigned len, const unsigned short array[len]);

/// Return the length of the convolution array
unsigned convolve_unit(unsigned char len, unsigned char kernel_len,
                       const unsigned short src[len],
                       unsigned short dest[len - kernel_len]);

unsigned forward_difference(unsigned char len, const unsigned short src[len],
                            unsigned short dest[len - 1]);
#endif // !__ARRAY_H__
