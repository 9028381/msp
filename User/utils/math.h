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
#define CLAMP(x, range) LIMIT(x, -range, range)

#endif // !__MATH_H__
