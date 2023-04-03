#ifndef _MATH_H
#define _MATH_H

#if 100 * __GNUC__ + __GNUC_MINOR__ >= 303
#define NAN      __builtin_nanf("")
#define INFINITY __builtin_inff()
#else
#define NAN      (0.0f / 0.0f)
#define INFINITY 1e5000f
#endif

#define HUGE_VALF INFINITY
#define HUGE_VAL  ((double)INFINITY)
#define HUGE_VALL ((long double)INFINITY)

#define M_PI 3.14159265358979323846 /* pi */

#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4

int __fpclassify(double);
int __fpclassifyf(float);
int __fpclassifyl(long double);

static __inline unsigned __FLOAT_BITS(float __f)
{
    union {
        float __f;
        unsigned __i;
    } __u;
    __u.__f = __f;
    return __u.__i;
}

static __inline unsigned long long __DOUBLE_BITS(double __f)
{
    union {
        double __f;
        unsigned long long __i;
    } __u;
    __u.__f = __f;
    return __u.__i;
}

#define fpclassify(x)                                 \
    (sizeof(x) == sizeof(float)    ? __fpclassifyf(x) \
     : sizeof(x) == sizeof(double) ? __fpclassify(x)  \
                                   : __fpclassifyl(x))

#define isnan(x)                                                                      \
    (sizeof(x) == sizeof(float)    ? (__FLOAT_BITS(x) & 0x7fffffff) > 0x7f800000      \
     : sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL >> 1) > 0x7ffULL << 52 \
                                   : __fpclassifyl(x) == FP_NAN)

#define isinf(x)                                                                       \
    (sizeof(x) == sizeof(float)    ? (__FLOAT_BITS(x) & 0x7fffffff) == 0x7f800000      \
     : sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL >> 1) == 0x7ffULL << 52 \
                                   : __fpclassifyl(x) == FP_INFINITE)

#define isfinite(x)                                                                   \
    (sizeof(x) == sizeof(float)    ? (__FLOAT_BITS(x) & 0x7fffffff) < 0x7f800000      \
     : sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL >> 1) < 0x7ffULL << 52 \
                                   : __fpclassifyl(x) > FP_INFINITE)

#define predict_false(x) (x)

long double roundl(long double x);
double rint(double x);
long long llrint(double);
double floor(double __x);
double sqrt(double __x);
double pow(double __x, double __y);
long long llroundl(long double __x);
double ceil(double __x);
double log(double __x);
double cos(double __x);
double fabs(double __x);
double sin(double __x);
double asin(double __x);
double round(double __x);
long double ceill(long double __x);

#endif