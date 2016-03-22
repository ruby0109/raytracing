#ifndef __RAY_MATH_TOOLKIT_H
#define __RAY_MATH_TOOLKIT_H

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <immintrin.h>

#define OPT 1

static inline
void normalize(double *v)
{
    double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    assert(d != 0.0 && "Error calculating normal");

    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

static inline
double length(const double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static inline
void add_vector(const double *a, const double *b, double *out)
{
    for (int i = 0; i < 3; i++)
        out[i] = a[i] + b[i];
}

static inline
void subtract_vector(const double *a, const double *b, double *out)
{
    __m256 out = 0.0;
    __m256 A = _mm_load_ps(a);
    __m256 B = _mm_load_ps(b);

    out = _mm_sub_ps( A, B);

    /*
    for (int i = 0; i < 3; i++)
        out[i] = a[i] - b[i];*/
}

static inline
void multiply_vectors(const double *a, const double *b, double *out)
{
    __m256 out = 0.0;
    __m256 A1 = _mm_load_ps(a);
    __m256 B1 = _mm_load_ps(b);

    out = _mm_mult_ps( A1, B1);
    /*
    for (int i = 0; i < 3; i++)
        out[i] = a[i] * b[i];*/
}

static inline
void multiply_vector(const double *a, double b, double *out)
{
    for (int i = 0; i < 3; i++)
        out[i] = a[i] * b;
}

static inline
void cross_product(const double *v1, const double *v2, double *out)
{
    /*
    __m256 out = 0.0;
    __m256 V1 = _mm_load_ps(v1);
    __m256 V2 = _mm_load_ps(v2);

    const uint32_t YZXMask = _MM_SHUFFLE( 1, 2, 0, 0 );
    const uint32_t ZXYMask = _MM_SHUFFLE( 2, 0, 1, 0 );
    
    __m256 cpTemp1 = _mm_shuffle_ps( V1, V1, YZXMask);
    __m256 cpTemp2 = _mm_shuffle_ps( V2, V2, ZXYMask);
    __m256 cpMult1 = _mm_mult_ps( cpTemp1, cpTemp2);
    
    cpTemp1 = _mm_shuffle_ps( V1, V1, ZXYMask);
    cpTemp2 = _mm_shuffle_ps( V2, V2, YZXMask);
    __m256 cpMult2 = _mm_mult_ps( cpTemp1, cpTemp2);
    
    out =  _mm_sub_ps( cpMult1, cpMult2);
    */
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];


}

static inline
double dot_product(const double *v1, const double *v2)
{
    __m256 dp = 0.0;
    __m256 V1 = _mm_load_ps(v1);
    __m256 V2 = _mm_load_ps(v2);
    
    __m256 dp += _mm_add_ps(dp, _mm_mul_ps(V1,V2)); 
    /*_mm128d dp = 0.0;

    for (int i = 0; i < 3; i++)
    {
        _mm128d x1 = _mmload_pd(v1[i]);
	_mm128d x2 = _mmload_pd(v2[i]);
        _mm128d dp += _mm_add_pd(dp, _mm_mul_pd(x1,x2);
    }*/
    return dp;
}

static inline
void scalar_triple_product(const double *u, const double *v, const double *w,
                           double *out)
{
    cross_product(v, w, out);
    multiply_vectors(u, out, out);
}

static inline
double scalar_triple(const double *u, const double *v, const double *w)
{
    double tmp[3];
    cross_product(w, u, tmp);
    return dot_product(v, tmp);
}

#endif
