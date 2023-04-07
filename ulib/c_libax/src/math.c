#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

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

// #define asuint64(f) ((union{double _f; uint64_t _i;}){f})._i
// #define asdouble(i) ((union{uint64_t _i; double _f;}){i})._f

// static inline uint32_t top12(double x)
// {
// 	return asuint64(x) >> 52;
// }

// #define issignalingf_inline(x) 0
// #define issignaling_inline(x) 0
// #ifndef fp_barrier
// #define fp_barrier fp_barrier
// static inline double fp_barrier(double x)
// {
// 	volatile double y = x;
// 	return y;
// }
// #endif
// #define SIGN_BIAS (0x800 << 7)
// #define WANT_ROUNDING 1

// static inline int zeroinfnan(uint64_t i)
// {
// 	return 2 * i - 1 >= 2 * asuint64(INFINITY) - 1;
// }

// static inline int checkint(uint64_t iy)
// {
// 	int e = iy >> 52 & 0x7ff;
// 	if (e < 0x3ff)
// 		return 0;
// 	if (e > 0x3ff + 52)
// 		return 2;
// 	if (iy & ((1ULL << (0x3ff + 52 - e)) - 1))
// 		return 0;
// 	if (iy & (1ULL << (0x3ff + 52 - e)))
// 		return 1;
// 	return 2;
// }

// double __math_invalid(double x)
// {
// 	return (x - x) / (x - x);
// }

// static inline double eval_as_double(double x)
// {
// 	double y = x;
// 	return y;
// }

// double __math_xflow(uint32_t sign, double y)
// {
// 	return eval_as_double(fp_barrier(sign ? -y : y) * y);
// }

// double __math_uflow(uint32_t sign)
// {
// 	return __math_xflow(sign, 0x1p-767);
// }

// double __math_oflow(uint32_t sign)
// {
// 	return __math_xflow(sign, 0x1p769);
// }

// #define OFF 0x3fe6955500000000
// #define POW_LOG_TABLE_BITS 7
// #define POW_LOG_POLY_ORDER 8
// #define N (1 << POW_LOG_TABLE_BITS)

// struct pow_log_data {
// 	double ln2hi;
// 	double ln2lo;
// 	double poly[POW_LOG_POLY_ORDER - 1]; /* First coefficient is 1.  */
// 	/* Note: the pad field is unused, but allows slightly faster indexing.  */
// 	struct {
// 		double invc, pad, logc, logctail;
// 	} tab[1 << POW_LOG_TABLE_BITS];
// } __pow_log_data;

// #define T __pow_log_data.tab
// #define A __pow_log_data.poly
// #define Ln2hi __pow_log_data.ln2hi
// #define Ln2lo __pow_log_data.ln2lo

// static inline double_t log_inline(uint64_t ix, double_t *tail)
// {
// 	/* double_t for better performance on targets with FLT_EVAL_METHOD==2.  */
// 	double_t z, r, y, invc, logc, logctail, kd, hi, t1, t2, lo, lo1, lo2, p;
// 	uint64_t iz, tmp;
// 	int k, i;

// 	/* x = 2^k z; where z is in range [OFF,2*OFF) and exact.
// 	   The range is split into N subintervals.
// 	   The ith subinterval contains z and c is near its center.  */
// 	tmp = ix - OFF;
// 	i = (tmp >> (52 - POW_LOG_TABLE_BITS)) % N;
// 	k = (int64_t)tmp >> 52; /* arithmetic shift */
// 	iz = ix - (tmp & 0xfffULL << 52);
// 	z = asdouble(iz);
// 	kd = (double_t)k;

// 	/* log(x) = k*Ln2 + log(c) + log1p(z/c-1).  */
// 	invc = T[i].invc;
// 	logc = T[i].logc;
// 	logctail = T[i].logctail;

// 	/* Note: 1/c is j/N or j/N/2 where j is an integer in [N,2N) and
//      |z/c - 1| < 1/N, so r = z/c - 1 is exactly representible.  */
// 	/* Split z such that rhi, rlo and rhi*rhi are exact and |rlo| <= |r|.  */
// 	double_t zhi = asdouble((iz + (1ULL << 31)) & (-1ULL << 32));
// 	double_t zlo = z - zhi;
// 	double_t rhi = zhi * invc - 1.0;
// 	double_t rlo = zlo * invc;
// 	r = rhi + rlo;

// 	/* k*Ln2 + log(c) + r.  */
// 	t1 = kd * Ln2hi + logc;
// 	t2 = t1 + r;
// 	lo1 = kd * Ln2lo + logctail;
// 	lo2 = t1 - t2 + r;

// 	/* Evaluation is optimized assuming superscalar pipelined execution.  */
// 	double_t ar, ar2, ar3, lo3, lo4;
// 	ar = A[0] * r; /* A[0] = -0.5.  */
// 	ar2 = r * ar;
// 	ar3 = r * ar2;
// 	/* k*Ln2 + log(c) + r + A[0]*r*r.  */
// 	double_t arhi = A[0] * rhi;
// 	double_t arhi2 = rhi * arhi;
// 	hi = t2 + arhi2;
// 	lo3 = rlo * (ar + arhi);
// 	lo4 = t2 - hi + arhi2;

// 	/* p = log1p(r) - r - A[0]*r*r.  */
// 	p = (ar3 * (A[1] + r * A[2] +
// 		    ar2 * (A[3] + r * A[4] + ar2 * (A[5] + r * A[6]))));
// 	lo = lo1 + lo2 + lo3 + lo4 + p;
// 	y = hi + lo;
// 	*tail = hi - y + lo;
// 	return y;
// }

// #define EXP_TABLE_BITS 7
// #define EXP_POLY_ORDER 5
// #define EXP_USE_TOINT_NARROW 0
// #define EXP2_POLY_ORDER 5

// struct exp_data {
// 	double invln2N;
// 	double shift;
// 	double negln2hiN;
// 	double negln2loN;
// 	double poly[4]; /* Last four coefficients.  */
// 	double exp2_shift;
// 	double exp2_poly[EXP2_POLY_ORDER];
// 	uint64_t tab[2*(1 << EXP_TABLE_BITS)];
// } __exp_data;

// #define InvLn2N __exp_data.invln2N
// #define NegLn2hiN __exp_data.negln2hiN
// #define NegLn2loN __exp_data.negln2loN
// #define Shift __exp_data.shift
// #define C2 __exp_data.poly[5 - EXP_POLY_ORDER]
// #define C3 __exp_data.poly[6 - EXP_POLY_ORDER]
// #define C4 __exp_data.poly[7 - EXP_POLY_ORDER]
// #define C5 __exp_data.poly[8 - EXP_POLY_ORDER]
// #define C6 __exp_data.poly[9 - EXP_POLY_ORDER]

// #ifndef fp_force_eval
// #define fp_force_eval fp_force_eval
// static inline void fp_force_eval(double x)
// {
// 	volatile double y;
// 	y = x;
// }
// #endif

// static inline double specialcase(double_t tmp, uint64_t sbits, uint64_t ki)
// {
// 	double_t scale, y;

// 	if ((ki & 0x80000000) == 0) {
// 		/* k > 0, the exponent of scale might have overflowed by <= 460.  */
// 		sbits -= 1009ull << 52;
// 		scale = asdouble(sbits);
// 		y = 0x1p1009 * (scale + scale * tmp);
// 		return eval_as_double(y);
// 	}
// 	/* k < 0, need special care in the subnormal range.  */
// 	sbits += 1022ull << 52;
// 	/* Note: sbits is signed scale.  */
// 	scale = asdouble(sbits);
// 	y = scale + scale * tmp;
// 	if (fabs(y) < 1.0) {
// 		/* Round y to the right precision before scaling it into the subnormal
// 		   range to avoid double rounding that can cause 0.5+E/2 ulp error where
// 		   E is the worst-case ulp error outside the subnormal range.  So this
// 		   is only useful if the goal is better than 1 ulp worst-case error.  */
// 		double_t hi, lo, one = 1.0;
// 		if (y < 0.0)
// 			one = -1.0;
// 		lo = scale - y + scale * tmp;
// 		hi = one + y;
// 		lo = one - hi + y + lo;
// 		y = eval_as_double(hi + lo) - one;
// 		/* Fix the sign of 0.  */
// 		if (y == 0.0)
// 			y = asdouble(sbits & 0x8000000000000000);
// 		/* The underflow exception needs to be signaled explicitly.  */
// 		fp_force_eval(fp_barrier(0x1p-1022) * 0x1p-1022);
// 	}
// 	y = 0x1p-1022 * y;
// 	return eval_as_double(y);
// }

// static inline double exp_inline(double_t x, double_t xtail, uint32_t sign_bias)
// {
// 	uint32_t abstop;
// 	uint64_t ki, idx, top, sbits;
// 	/* double_t for better performance on targets with FLT_EVAL_METHOD==2.  */
// 	double_t kd, z, r, r2, scale, tail, tmp;

// 	abstop = top12(x) & 0x7ff;
// 	if (predict_false(abstop - top12(0x1p-54) >=
// 			  top12(512.0) - top12(0x1p-54))) {
// 		if (abstop - top12(0x1p-54) >= 0x80000000) {
// 			/* Avoid spurious underflow for tiny x.  */
// 			/* Note: 0 is common input.  */
// 			double_t one = WANT_ROUNDING ? 1.0 + x : 1.0;
// 			return sign_bias ? -one : one;
// 		}
// 		if (abstop >= top12(1024.0)) {
// 			/* Note: inf and nan are already handled.  */
// 			if (asuint64(x) >> 63)
// 				return __math_uflow(sign_bias);
// 			else
// 				return __math_oflow(sign_bias);
// 		}
// 		/* Large x is special cased below.  */
// 		abstop = 0;
// 	}

// 	/* exp(x) = 2^(k/N) * exp(r), with exp(r) in [2^(-1/2N),2^(1/2N)].  */
// 	/* x = ln2/N*k + r, with int k and r in [-ln2/2N, ln2/2N].  */
// 	z = InvLn2N * x;

// 	/* z - kd is in [-1, 1] in non-nearest rounding modes.  */
// 	kd = eval_as_double(z + Shift);
// 	ki = asuint64(kd);
// 	kd -= Shift;

// 	r = x + kd * NegLn2hiN + kd * NegLn2loN;
// 	/* The code assumes 2^-200 < |xtail| < 2^-8/N.  */
// 	r += xtail;
// 	/* 2^(k/N) ~= scale * (1 + tail).  */
// 	idx = 2 * (ki % N);
// 	top = (ki + sign_bias) << (52 - EXP_TABLE_BITS);
// 	tail = asdouble(T[idx]);
// 	/* This is only a valid scale when -1023*N < k < 1024*N.  */
// 	sbits = T[idx + 1] + top;
// 	/* exp(x) = 2^(k/N) * exp(r) ~= scale + scale * (tail + exp(r) - 1).  */
// 	/* Evaluation is optimized assuming superscalar pipelined execution.  */
// 	r2 = r * r;
// 	/* Without fma the worst case error is 0.25/N ulp larger.  */
// 	/* Worst case error is less than 0.5+1.11/N+(abs poly error * 2^53) ulp.  */
// 	tmp = tail + r + r2 * (C2 + r * C3) + r2 * r2 * (C4 + r * C5);
// 	if (predict_false(abstop == 0))
// 		return specialcase(tmp, sbits, ki);
// 	scale = asdouble(sbits);
// 	/* Note: tmp == 0 or |tmp| > 2^-200 and scale > 2^-739, so there
// 	   is no spurious underflow here even without fma.  */
// 	return eval_as_double(scale + scale * tmp);
// }

double pow(double x, double y)
{
	// uint32_t sign_bias = 0;
	// uint64_t ix, iy;
	// uint32_t topx, topy;

	// ix = asuint64(x);
	// iy = asuint64(y);
	// topx = top12(x);
	// topy = top12(y);
	// if (predict_false(topx - 0x001 >= 0x7ff - 0x001 ||
	// 		  (topy & 0x7ff) - 0x3be >= 0x43e - 0x3be)) {
	// 	/* Note: if |y| > 1075 * ln2 * 2^53 ~= 0x1.749p62 then pow(x,y) = inf/0
	// 	   and if |y| < 2^-54 / 1075 ~= 0x1.e7b6p-65 then pow(x,y) = +-1.  */
	// 	/* Special cases: (x < 0x1p-126 or inf or nan) or
	// 	   (|y| < 0x1p-65 or |y| >= 0x1p63 or nan).  */
	// 	if (predict_false(zeroinfnan(iy))) {
	// 		if (2 * iy == 0)
	// 			return issignaling_inline(x) ? x + y : 1.0;
	// 		if (ix == asuint64(1.0))
	// 			return issignaling_inline(y) ? x + y : 1.0;
	// 		if (2 * ix > 2 * asuint64(INFINITY) ||
	// 		    2 * iy > 2 * asuint64(INFINITY))
	// 			return x + y;
	// 		if (2 * ix == 2 * asuint64(1.0))
	// 			return 1.0;
	// 		if ((2 * ix < 2 * asuint64(1.0)) == !(iy >> 63))
	// 			return 0.0; /* |x|<1 && y==inf or |x|>1 && y==-inf.  */
	// 		return y * y;
	// 	}
	// 	if (predict_false(zeroinfnan(ix))) {
	// 		double_t x2 = x * x;
	// 		if (ix >> 63 && checkint(iy) == 1)
	// 			x2 = -x2;
	// 		/* Without the barrier some versions of clang hoist the 1/x2 and
	// 		   thus division by zero exception can be signaled spuriously.  */
	// 		return iy >> 63 ? fp_barrier(1 / x2) : x2;
	// 	}
	// 	/* Here x and y are non-zero finite.  */
	// 	if (ix >> 63) {
	// 		/* Finite x < 0.  */
	// 		int yint = checkint(iy);
	// 		if (yint == 0)
	// 			return __math_invalid(x);
	// 		if (yint == 1)
	// 			sign_bias = SIGN_BIAS;
	// 		ix &= 0x7fffffffffffffff;
	// 		topx &= 0x7ff;
	// 	}
	// 	if ((topy & 0x7ff) - 0x3be >= 0x43e - 0x3be) {
	// 		/* Note: sign_bias == 0 here because y is not odd.  */
	// 		if (ix == asuint64(1.0))
	// 			return 1.0;
	// 		if ((topy & 0x7ff) < 0x3be) {
	// 			/* |y| < 2^-65, x^y ~= 1 + y*log(x).  */
	// 			if (WANT_ROUNDING)
	// 				return ix > asuint64(1.0) ? 1.0 + y :
	// 							    1.0 - y;
	// 			else
	// 				return 1.0;
	// 		}
	// 		return (ix > asuint64(1.0)) == (topy < 0x800) ?
	// 			       __math_oflow(0) :
	// 			       __math_uflow(0);
	// 	}
	// 	if (topx == 0) {
	// 		/* Normalize subnormal x so exponent becomes negative.  */
	// 		ix = asuint64(x * 0x1p52);
	// 		ix &= 0x7fffffffffffffff;
	// 		ix -= 52ULL << 52;
	// 	}
	// }

	// double_t lo;
	// double_t hi = log_inline(ix, &lo);
	// double_t ehi, elo;

	// double_t yhi = asdouble(iy & -1ULL << 27);
	// double_t ylo = y - yhi;
	// double_t lhi = asdouble(asuint64(hi) & -1ULL << 27);
	// double_t llo = hi - lhi + lo;
	// ehi = yhi * lhi;
	// elo = ylo * lhi + y * llo; /* |elo| < |ehi| * 2^-25.  */
	// return exp_inline(ehi, elo, sign_bias);
}

// Note: this is an architechture dependent implementation
double round(double x)
{
	__asm__ ("frinta %d0, %d1" : "=w"(x) : "w"(x));
	return x;
}

long double roundl(long double x)
{
	return round(x);
}

long long llroundl(long double x)
{
	return roundl(x);
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
	return ceil(x);
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