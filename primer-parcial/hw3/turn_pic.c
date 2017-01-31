/*
Margot Duek 
Turned picture
30/01/2017
Advanced programming
*/


#include <stdio.h>
#include "Turn_pic.h"
#include <cstdlib>
 
int main(){
  struct matrix picture;
  picture.rows = 5;
  picture.cols = 5;
  picture.mat = create_matrix(picture.rows, picture.cols);
  fillRandomMatrix(picture.mat, picture.rows, picture.cols);
  print_matrix(picture.mat, picture.rows, picture.cols);
  turn_picture(picture.mat, picture.rows, picture.cols);
  print_matrix(picture.mat, picture.rows, picture.cols);
  return 0;
}


int ** create_matrix(int rows, int cols)
{
  int i;
  int ** retVal = (int **) malloc(sizeof(int *)*rows);
  for (i = 0; i < rows; i++) {
    retVal[i] = (int *) malloc(sizeof(int)*cols);
  }
  return retVal;
}



void fillRandomMatrix(int ** matrix, int rows, int cols)
{
  int i, j;
  int data = 1;

  for (i=0; i<rows; i++)
    {
      for (j=0; j<cols; j++)
	{
	  matrix[i][j] = data++;
	}
    }
}

void turn_picture(int ** matrix, int rows, int cols){
  int i, j;
  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      matrix[i][j] = 255 - matrix[i][j];
    }
  }
}



void print_matrix(int ** matrix, int rows, int cols)
{
  int i, j;

  for (i=0; i<rows; i++)
    {
      for (j=0; j<cols; j++)
	{
	  printf("%10.2d", matrix[i][j]);
	}
      printf("\n");
    }
  printf("\n");
}
