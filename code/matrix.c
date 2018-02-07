#include "matrix.h"

p_mat createMat(int row, int col)
{
  p_mat pointer;
  pointer = (p_mat)malloc(sizeof(mat));
  if(pointer == NULL) return 0;
  pointer->value = (float*)malloc(sizeof(float)*row*col);
  pointer->row = row;
  pointer->col = col;
  return pointer;
}

void Init(p_mat pointer)
{
  int i, j, m, n;
  m = pointer->row;
  n = pointer->col;
  for(i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
    {
      *(pointer->value + i * pointer->col + j) = 0;
    }
  }
}

char readMat(FILE *fp, p_mat pointer)
{
  int row, col;
  int i, j;
  fscanf(fp, "%d %d", &row, &col);
  if((pointer->row == row) && (pointer->col == col))
  {
  for(i = 0; i < row; i++){
    for(j = 0; j < col; j++){
      fscanf(fp, "%f", (pointer->value + i * pointer->col + j));
      }
    }
  }
  else return 0;
  return 1;
}

void showMat(p_mat pointer)
{
  int i, j;
  for(i = 0; i < pointer->row; i++){
    for(j = 0; j < pointer->col; j++){
      printf("%-1.3f\t", *(pointer->value + i * pointer->col + j));
    }
    printf("\n");
  }
  printf("\n");
}

void multiply(const p_mat matrix_a, const p_mat matrix_b, p_mat res)
{
  int i, j, k, m, s, n;
  m = matrix_a->row;
  s = matrix_a->col; // also equal to matrix_b->row
  n = matrix_b->col;
  for(i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
    {
      *(res->value + i * res->col + j) = 0;
      for(k = 0; k < s; k++)
      {
        *(res->value + i * res->col + j) += *(matrix_a->value + i * matrix_a->col + k) * *(matrix_b->value + k * matrix_b->col + j);
      }
    }
  }
}


