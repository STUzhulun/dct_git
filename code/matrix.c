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
  if(2 != fscanf(fp, "%d %d", &row, &col)) exit(1);
  if((pointer->row == row) && (pointer->col == col))
  {
  for(i = 0; i < row; i++){
    for(j = 0; j < col; j++){
      if(1 != fscanf(fp, "%f", (pointer->value + i * pointer->col + j))) exit(1);
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
  if(matrix_a->col != matrix_b->row) 
  {
    printf("the matrixs can't be operated multiply.\n");
    exit(0);
  }
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

void dct(const p_mat input, p_mat res)
{
  p_mat s[4], mid;
  FILE *fp_s[4], *fp_input;
  char file_name[64] = {0};
  int num, i, j, k;
  for(num = 0; num < 4; num++)
  {
    sprintf(file_name, "matrix_s%d", num+1);
    if((fp_s[num] = fopen(file_name,"r")) == NULL)
    {
      printf("Can't open the \"matrix_s%d\" file.\n",num+1);
      exit(1);
    }
  }
  mid = createMat(N, 1);
  for(num = 0; num < 4; num++)
  {
    s[num] = createMat(N, N);
    if(readMat(fp_s[num], s[num]))
    {
      //showMat(s[num]);
      fclose(fp_s[num]);
    }
    else
    {
      printf("can't read matrix form file.\n");
      exit(1);
    }
  }
  multiply(s[0], input, mid);
  multiply(s[1], mid, res);
  multiply(s[2], res, mid);
  for(i = 0; i < s[3]->row; i++)
  {
    for(j = 0; j < mid->col; j++)
    {
      *(res->value + i * res->col + j) = 0;
      for(k = 0; k < s[3]->col; k++)
      {
        *(res->value + i * res->col + j) += *(s[3]->value + i * s[3]->col + k) * *(mid->value + k * mid->col + j);
      }
    }
    if(i == 0) *(res->value + i * res->col + j-1) *= sqrt(1.0/N);
    else *(res->value + i * res->col + j-1) *= 0.5; 
  }  
}

