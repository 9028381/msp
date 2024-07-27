#ifndef __MATH_H__
#define __MATH_H__

/// Archimedes' constant (π)
#define PI 3.14159265358979323846264338327950288

/// Full circle constant (τ) τ = 2π
#define TAU 6.28318530717958647692528676655900577

/// Euler's number (e)
#define E 2.71828182845904523536028747135266250

/// Golden ratio (φ)
#define PHI 1.61803398874989484820458683436563811

/// Computes the absolute value of `x`.
///
/// Returns `-x` if `x` is negative,
/// Otherwise this returns `x`.
///
/// Equivalent expression `x >= 0 ? x : -x`.
///
/// # Example
///
/// ```c
/// int x = -1;
/// assert(ABS(x) == 1);
///
/// int y = 1;
/// assert(ABS(y) == 1);
/// ```
#define ABS(x) ((x) >= 0 ? (x) : -(x))

/// Computes the maximum value of `x` and `y`.
///
/// Equivalent expression `x > y ? x : y`.
///
/// # Example
///
/// ```c
/// int x = 1, y = 2;
/// assert(MAX(x, y) == 2);
/// ```
#define MAX(x, y) ((x) > (y) ? (x) : (y))

/// Computes the minimum value of `x` and `y`.
///
/// Equivalent expression `x < y ? x : y`.
///
/// # Example
///
/// ```c
/// int x = 1, y = 2;
/// assert(MIN(x, y) == 1);
/// ```
#define MIN(x, y) ((x) < (y) ? (x) : (y))

/// Limit the maximum value of `x` to no more than `max`
///
/// Returns `max` if `x` is more than `max`,
/// Otherwise this returns `x`.
///
/// Equivalent expression `x <= max ? x : max`.
///
/// # Example
///
/// ```c
/// int x = 1, max = 2;
/// assert(LIMIT_MAX(x, max) == 1);
///
/// assert(LIMIT_MAX(3, 2) == 2);
/// ```
#define LIMIT_MAX(x, max) MIN(x, max)

/// Limit the minimum value of `x` to no less than `min`
///
/// Returns `min` if `x` is less than `min`,
/// Otherwise this returns `x`.
///
/// Equivalent expression `x >= min ? x : min`.
///
/// # Example
///
/// ```c
/// int x = 3, min = 2;
/// assert(LIMIT_MIN(x, min) == 3);
///
/// assert(LIMIT_MIN(1, 2) == 2);
/// ````
#define LIMIT_MIN(x, min) MAX(x, min)

/// Restrict `x` to a certain interval [min, max]
///
/// Returns `max` if `x` is greater than `max`,
///     and `min` if `x` is less than `min`,
///     otherwise this returns `x.
///
/// Equivalent expression
///   v = LIMIT_MAX(x, max)
///   v = LIMIT_MIN(v, min)
///
/// # Warning
/// `min` must be less than `max`.
///
/// # Example
///
/// ```c
/// int x = 3, min = 2, max = 4;
/// assert(LIMIT(x, min, max) == 3);
///
/// assert(LIMIT(1, 2, 4) == 2);
/// assert(LIMIT(5, 2, 4) == 4);
/// ```
#define LIMIT(x, min, max) LIMIT_MIN(LIMIT_MAX(x, max), min)

/// Restrict `x` to a certain interval [-range, range]
///
/// Returns `range` if `x` is greater than `range`,
///     and `-range` if `x` is less than `-range`,
///     otherwise this returns `x.
///
/// Equivalent expression
///   v = LIMIT(x, -range, range)
///
/// # Warning
/// `range` must be greater than 0.
///
/// # Example
///
/// ```c
/// int x = 3, range = 4;
/// assert(CLAMP(x, range) == 3);
///
/// assert(CLAMP(5, 4) == 4);
/// assert(CLAMP(-5, 4) == -4);
/// ```
#define CLAMP(x, range) LIMIT(x, -(range), range)

#define WARPPING_FN_DECLARE(type)                                              \
  type warpping_##type(type var, type min, type max);

WARPPING_FN_DECLARE(float)
WARPPING_FN_DECLARE(double)

WARPPING_FN_DECLARE(long)
WARPPING_FN_DECLARE(int)
WARPPING_FN_DECLARE(short)
WARPPING_FN_DECLARE(char)

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

WARPPING_FN_DECLARE(ulong)
WARPPING_FN_DECLARE(uint)
WARPPING_FN_DECLARE(ushort)
WARPPING_FN_DECLARE(uchar)

#define WARPPING_FN_GENERIC(x)                                                 \
  _Generic((x),                                                                \
      double: warpping_double,                                                 \
      float: warpping_float,                                                   \
      long: warpping_long,                                                     \
      int: warpping_int,                                                       \
      short: warpping_short,                                                   \
      char: warpping_char,                                                     \
      ulong: warpping_ulong,                                                   \
      uint: warpping_uint,                                                     \
      ushort: warpping_ushort,                                                 \
      uchar: warpping_uchar)

/// Warps `var` from `min` to `max`. [min, max]
///
/// range = max - min
/// n is make sure `var +/- range * n` is between `min` and `max`
///
/// Returns `var` if `var` is between `min` and `max`,
///     and `var + range * n` if `var` is less than `min`,
///     and `var - range * n` if `var` is greater than `max`.
///
/// # Warning
/// `min` must be less than `max`.
///
/// # Example
///
/// ```c
/// int x = 3, min = 2, max = 4;
/// assert(WARPPING(x, min, max) == 3);
/// assert(WARPPING(1, min, max) == 3);
/// assert(WARPPING(5, min, max) == 3);
/// ```
#define WARPPING(var, min, max) WARPPING_FN_GENERIC(var)(var, min, max)

#endif // !__MATH_H__
