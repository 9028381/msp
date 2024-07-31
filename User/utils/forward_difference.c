unsigned forward_difference(unsigned char len, const unsigned short src[len],
                            unsigned short dest[len - 1]) {
  if (len == 0)
    return 0;

  for (unsigned char i = 0; i < len - 1; i++)
    dest[i] = src[i + 1] - src[i];

  return len - 1;
}
