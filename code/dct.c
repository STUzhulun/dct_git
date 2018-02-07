#include "dct.h"


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
  if(s[3]->col != mid->row)
  {
    printf("the matrixs can't be operated multiply.\n");
    exit(0);
  }
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

