#ifndef _DCT_H_
#define _DCT_H_

#include "matrix.h"
#include <math.h>
#define N 8
#define PI 3.1415926
#define xita (5.0*PI/8.0)

void dct(const p_mat, p_mat);
void my_fast_dct(const p_mat, p_mat);
void scaled_dct_s1s2(const p_mat, p_mat);
void scaled_dct_s3d8(const p_mat, p_mat);

#endif
