#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

/// Return the length of the convolution array
unsigned convolve_unit(unsigned char len, unsigned char kernel_len,
                       const unsigned short src[len],
                       unsigned short dest[len - kernel_len]);

#endif // !__CONVOLUTION_H__
