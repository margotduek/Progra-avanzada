#include <stdio.h>
#include <stdlib.h>
#define CHUNK 1024 /* read 1024 bytes at the time */
#define sizeA 3
#define sizeB 3



int main(){

  // Alocating dinamic space
  float** mata=malloc(1000000*sizeof(float*));
  for(int i=0;i<1000000;++i)
    mata[i]=malloc(4*sizeof(float));

  // Opening a file for reading 
  FILE *a = fopen("matrixA.txt", "r");

  // saving the numbers of the file in a matrix
  for(int i = 0; i < 3; i ++){
    for(int j = 0; j < 3 ; j++){
      if(!fscanf(a, "%f", &mata[i][j]))
	break;
    }
  }
  fclose(a);


  float** matb=malloc(1000000*sizeof(float*));
  for(int i=0;i<1000000;++i)
    matb[i]=malloc(4*sizeof(float));
  
  FILE *b = fopen("matrixB.txt", "r");

  for(int i = 0; i < 3; i ++){
    for(int j = 0; j < 3 ; j++){
      if(!fscanf(b, "%f", &matb[i][j]))
	break;
      //printf("%lf\n", matb[i][j]);
    }
  }
  fclose(b);


  //result matrix 
  float C[3][3];
  // Initializing all elements of result matrix to 0
  for(int i=0; i<3; ++i)
    for(int j=0; j<3; ++j)
      {
	C[i][j] = 0;
      }
  
  
  // multiplication logic 
  for(int i=0; i < 3; ++i)
    for(int j=0; j < 3; ++j)
      for(int k=0; k < 3; ++k)
	{
	  C[i][j]+=mata[i][k]*matb[k][j];
	}
  
  printf("\nMultiplication Of Two Matrices : \n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf(" %f", C[i][j]);
    }
    printf("\n");
  }

  
  return 0;
}
