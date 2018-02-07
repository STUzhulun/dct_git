#ifndef _MATRIX_H_
#define _MATRIX_H_
#define N 8

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct MATRIX {
  int row, col;
  float *value;
};
typedef struct MATRIX mat;
typedef struct MATRIX* p_mat;

p_mat createMat(int, int);
void Init(p_mat);
char readMat(FILE *, p_mat);
void showMat(p_mat);
void multiply(const p_mat, const p_mat, p_mat);
void dct(const p_mat, p_mat);

#endif
