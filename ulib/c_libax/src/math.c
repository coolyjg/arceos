#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int __eqtf2 (long double a, long double b)
{
	return a == b;
}

int __gttf2 (long double a, long double b)
{
	return a > b;
}

long double __floatditf (long i)
{
	return 0;
}

long double __extenddftf2 (double a)
{
	return 0;
}

long double __addtf3 (long double a, long double b)
{
	return a + b;
}

long double __multf3 (long double a, long double b)
{
	return a * b;
}

double __trunctfdf2 (long double a)
{
	return 0;
}

long __fixtfdi (long double a)
{
	return 0;
}

int __fpclassify(double x)
{
	union {double f; uint64_t i;} u = {x};
	int e = u.i>>52 & 0x7ff;
	if (!e) return u.i<<1 ? FP_SUBNORMAL : FP_ZERO;
	if (e==0x7ff) return u.i<<12 ? FP_NAN : FP_INFINITE;
	return FP_NORMAL;
}

int __fpclassifyf(float x)
{
	union {float f; uint32_t i;} u = {x};
	int e = u.i>>23 & 0xff;
	if (!e) return u.i<<1 ? FP_SUBNORMAL : FP_ZERO;
	if (e==0xff) return u.i<<9 ? FP_NAN : FP_INFINITE;
	return FP_NORMAL;
}

int __fpclassifyl(long double x)
{
	union {double f; uint64_t i;} u = {x};
	int e = u.i>>52 & 0x7ff;
	if (!e) return u.i<<1 ? FP_SUBNORMAL : FP_ZERO;
	if (e==0x7ff) return u.i<<12 ? FP_NAN : FP_INFINITE;
	return FP_NORMAL;
	// return __fpclassify(x);
}

// Note: this is an architechture dependent implementation
double rint(double x)
{
	__asm__ ("frintx %d0, %d1" : "=w"(x) : "w"(x));
	return x;
}

long long llrint(double x)
{
    return rint(x);
}

// Note: this is an architechture dependent implementation
double floor(double x)
{
    __asm__ ("frintm %d0, %d1" : "=w"(x) : "w"(x));
	return x;
}

// Note: this is an architechture dependent implementation
double sqrt(double x)
{
    __asm__ ("fsqrt %d0, %d1" : "=w"(x) : "w"(x));
	return x;
}

// TODO
double pow(double x, double y)
{
	return 0;
}

// Note: this is an architechture dependent implementation
double round(double x)
{
	__asm__ ("frinta %d0, %d1" : "=w"(x) : "w"(x));
	return x;
}

long double roundl(long double x)
{
	__asm__ ("frinta %d0, %d1" : "=w"(x) : "w"(x));
	return x;
	// return round(x);
}

long long llroundl(long double x)
{
	__asm__ ("frinta %d0, %d1" : "=w"(x) : "w"(x));
	return x;
	// return roundl(x);
}

double ceil(double x)
{
	__asm__ ("frintp %d0, %d1" : "=w"(x) : "w"(x));
	return x;
}

// TODO
double log(double __x)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

double fabs(double x)
{
	__asm__ ("fabs %d0, %d1" : "=w"(x) : "w"(x));
	return x;
}

// TODO
double sin(double __x)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
double asin(double __x)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

long double ceill(long double x)
{
	__asm__ ("frintp %d0, %d1" : "=w"(x) : "w"(x));
	return x;
	// return ceil(x);
}

//TODO
double acos(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double atan(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double atan2(double, double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double cosh(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double exp(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double fmod(double, double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double frexp(double, int *)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double ldexp(double, int)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double log10(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double modf(double, double *)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double sinh(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double tan(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double tanh(double)
{
	printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}