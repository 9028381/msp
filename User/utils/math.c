#define WARPPING_FUNC_DECLARE(type)                                            \
  type warpping_##type(type var, type min, type max) {                         \
    type range = max - min;                                                    \
    while (var > max)                                                          \
      var -= range;                                                            \
    while (var < min)                                                          \
      var += range;                                                            \
    return var;                                                                \
  }

WARPPING_FUNC_DECLARE(float)
WARPPING_FUNC_DECLARE(int)
WARPPING_FUNC_DECLARE(short)
