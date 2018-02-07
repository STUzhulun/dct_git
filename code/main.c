#include "matrix.h"


int  main(int argc ,char* argv[]) 
{
  p_mat res, x;
  int num;
  FILE *fp_input;
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

  res = createMat(N, 1);
  dct(x,res);

  printf("Its DCT trasnsform X[k] is followed...\n");
  showMat(res);
  return 0;
}
