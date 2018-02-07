#include "matrix.h"
#define N 8

int  main(int argc ,char* argv[]) 
{
  p_mat s[4], res, x, mid;
  int num;
  FILE *fp_s[4], *fp_input;
  char file_name[64] = {0};
  for(num = 0; num < 4; num++)
  {
    sprintf(file_name, "matrix_s%d", num+1);
    if((fp_s[num] = fopen(file_name,"r")) == NULL)
    {
      printf("Can't open the \"matrix_s%d\" file.\n",num+1);
      exit(1);
    }
  }
  
  printf("The sequence x[n] is followed...\n");
  if((fp_input = fopen("input","r")) == NULL)
  {
    printf("Can't open the \"input\" file.\n");
    exit(1);
  }
  x = createMat(N, 1);
  if(readMat(fp_input, x))
  {
    showMat(x);
    fclose(fp_input);
  }
  else
  {
    printf("can't read matrix form file.\n");
    exit(1);
  }
  
  mid = createMat(N, 1);
  res = createMat(N, 1);
  
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
  
  
  multiply(s[0], x, mid);
  multiply(s[1], mid, res);
  multiply(s[2], res, mid);
  multiply(s[3], mid, res);
  printf("Its DCT trasnsform X[k] is followed...\n");
  showMat(res);
  return 0;
}
