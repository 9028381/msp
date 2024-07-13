#ifndef __MATH_H__
#define __MATH_H__

#define PI 3.14159265358979323846
#define E 2.71828182845904523536

#define ABS(x) ((x) >= 0 ? (x) : -(x))

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define LIMIT_MAX(x, max) MIN(x, max)
#define LIMIT_MIN(x, min) MAX(x, min)
#define LIMIT(x, min, max) LIMIT_MIN(LIMIT_MAX(x, max), min)
#define CLAMP(x, range) LIMIT(x, -(range), range)

#define WARPPING_FUN_DECLARE(type)                                             \
  type warpping_##type(type var, type min, type max);

WARPPING_FUN_DECLARE(float)
WARPPING_FUN_DECLARE(int)
WARPPING_FUN_DECLARE(short)

#define WARPPING_FUN(x)                                                        \
  _Generic((x), int: warpping_int, short: warpping_short, float: warpping_float)

#define WARPPING(var, min, max) WARPPING_FUN(var)(var, min, max)

#endif // !__MATH_H__
