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
/*
void dct_simple(const p_mat input, p_mat res)
{
  int i, j, k;
  Init(res);
  for(i = 0; i < res->row; i++)
  {
    for(j = 0; j < res->col; j++)
    {
      switch(i)
      {
        case 0:
          for(k = 0; k < input->row; k++) 
            *(res->value) += *(input->value+ k);
          break;
        case 1:
          *(res->value + 1) = *(input->value)         
      }
      
    }
  }
  
}
*/

void my_fast_dct(const p_mat input, p_mat res)
{
  float mid_1[8], mid_2[8], temp1, temp2;
  mid_1[0] =  *(input->value + 0) + *(input->value + 7);
  mid_1[1] =  *(input->value + 1) + *(input->value + 6);
  mid_1[2] =  *(input->value + 2) + *(input->value + 5);
  mid_1[3] =  *(input->value + 3) + *(input->value + 4);
  mid_1[4] = -*(input->value + 4) + *(input->value + 3);
  mid_1[5] = -*(input->value + 5) + *(input->value + 2);
  mid_1[6] = -*(input->value + 6) + *(input->value + 1);
  mid_1[7] = -*(input->value + 7) + *(input->value + 0);
  
  mid_2[0] =  mid_1[0] + mid_1[3];
  mid_2[1] =  mid_1[1] + mid_1[2];
  mid_2[2] = -mid_1[2] + mid_1[1];
  mid_2[3] = -mid_1[3] + mid_1[0];
  temp1 = -(13.0/32.0) * mid_1[6] + mid_1[5];
  temp2 =  (11.0/16.0) * temp1 + mid_1[6];
  temp1 =  (13.0/32.0) * temp2 - temp1;
  mid_2[4] = mid_1[4] + temp1;
  mid_2[5] = mid_1[4] - temp1;
  mid_2[6] = mid_1[7] - temp2;
  mid_2[7] = mid_1[7] + temp2;
  
  mid_1[0] =  mid_2[0] + mid_2[1];
  mid_1[1] = -mid_2[1] + ( 1.0/ 2.0) * mid_2[0];
  mid_1[2] = -mid_2[2] + (13.0/32.0) * mid_2[3];
  mid_1[3] =  mid_2[3] - (11.0/32.0) * mid_2[2];
  mid_1[4] = -mid_2[4] + ( 3.0/26.0) * mid_2[7];
  mid_1[5] =  mid_2[5] + (11.0/16.0) * mid_2[6];
  mid_1[6] =  mid_2[6] - (15.0/32.0) * mid_2[5];
  mid_1[7] =  mid_2[7] - ( 3.0/16.0) * mid_2[4];

    
  Init(res);
  *(res->value + 0) = mid_1[0] * (0.5*sin(1*PI/ 4.0));
  *(res->value + 1) = mid_1[7] / (2.0*sin(7*PI/16.0));
  *(res->value + 2) = mid_1[3] / (2.0*sin(3*PI/ 8.0));
  *(res->value + 3) = mid_1[6] / (2.0*cos(3*PI/16.0));
  *(res->value + 4) = mid_1[1] * (1.0*sin(1*PI/ 4.0));
  *(res->value + 5) = mid_1[5] * (0.5*cos(3*PI/16.0));
  *(res->value + 6) = mid_1[2] * (0.5*sin(3*PI/ 8.0));
  *(res->value + 7) = mid_1[4] * (0.5*sin(7*PI/16.0));
  
}



void scaled_dct_s1s2(const p_mat input, p_mat res)
{
	float temp1 = 0, temp2 = 0, temp3 = 0, temp4 =0;
	float P = 0, U = 0;
	Init(res);
	*(res->value+0) = + *(input->value+0) + *(input->value+1)
					          + *(input->value+2) + *(input->value+3)
					          + *(input->value+4) + *(input->value+5)
					          + *(input->value+6) + *(input->value+7);
	
	*(res->value+1) = + *(input->value+0) - *(input->value+1)
					          - *(input->value+2) + *(input->value+3)
					          + *(input->value+4) - *(input->value+5)
					          - *(input->value+6) + *(input->value+7);
					  
	*(res->value+2) = 					          + *(input->value+1)
					          - *(input->value+2) 
										                    - *(input->value+5)
					          + *(input->value+6) 	        				 ;	

	*(res->value+3) =(+ *(input->value+0) - *(input->value+1)
					          + *(input->value+2) - *(input->value+3)
					          - *(input->value+4) + *(input->value+5)
					          - *(input->value+6) + *(input->value+7))*(sqrt(2.0)/2.0);

	*(res->value+4) = 
					          - *(input->value+2) 
										                    + *(input->value+5)
															                             ;

	*(res->value+5) =(- *(input->value+0) 
										                    + *(input->value+3)
					          - *(input->value+4)
										                    + *(input->value+7))*(-sqrt(2.0)/2.0);


	P = -tan(xita/2.0); U = sin(xita);
	
	temp1 = + *(input->value+0)
			    - *(input->value+2)
								              + *(input->value+5)
								              - *(input->value+7);
										  
	temp2 = 					          + *(input->value+1)
								              + *(input->value+3)
			    - *(input->value+4) 
			    - *(input->value+6) 				   ; 
			    
	
	temp3 = temp1 + P * temp2;
	temp4 = temp2;

	temp1 = temp3;
	temp2 = U * temp3 + temp4;		

	*(res->value+6) = temp1 + P * temp2;
	
	
	*(res->value+7) = temp2;
										  
}


void scaled_dct_s3d8(const p_mat input, p_mat res)
{
	Init(res);
	*(res->value+0) =(+ *(input->value+0)					           )*sqrt(1.0/N); 
	
	*(res->value+1) =(- *(input->value+4) + *(input->value+5)
					          - *(input->value+6)					           )/(4*cos(5.0*PI/16.0));
					  
	*(res->value+2) =(+ *(input->value+2) + *(input->value+3))/(4*cos(6.0*PI/16.0));
	
	*(res->value+3) =(+ *(input->value+4) + *(input->value+5)
										                    + *(input->value+7))/(4*cos(1.0*PI/16.0));
										  
	*(res->value+4) =(					          + *(input->value+1))/(4*cos(4.0*PI/16.0));
	
	*(res->value+5) =(- *(input->value+4) - *(input->value+5)
										                    + *(input->value+7))/(4*cos(7.0*PI/16.0));
										  
	*(res->value+6) =(- *(input->value+2) + *(input->value+3))/(4*cos(2.0*PI/16.0));
	
	*(res->value+7) =(- *(input->value+4) + *(input->value+5)
					          + *(input->value+6) 					         )/(4*cos(3.0*PI/16.0));

}
