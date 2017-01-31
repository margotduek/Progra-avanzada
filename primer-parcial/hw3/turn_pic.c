/*
Margot Duek 
Turned picture
30/01/2017
Advanced programming
*/


#include <stdio.h>
#include "Turn_pic.h"
#include <cstdlib>
#define MAX_ROW 6 //5500
#define MAX_COL 3 //520

int main(){
  struct matrix picture;
  std::string file = "mini.ppm";
  picture.rows = MAX_COL;
  picture.cols = MAX_ROW;
  picture.mat = create_matrix(picture.rows, picture.cols);
  read_file(picture.mat, file);
  //fillRandomMatrix(picture.mat, picture.rows, picture.cols);
  print_matrix(picture.mat, picture.rows, picture.cols);
 
  turn_picture(picture.mat, picture.rows, picture.cols);
  print_matrix(picture.mat, picture.rows, picture.cols);
 export_matrix(picture.mat, picture.rows, picture.cols);
  return 0;
}

void read_file(int **matrix, std::string file){
  // Opening a file for reading 
  FILE *a = fopen( "mini.ppm", "r");

  // saving the numbers of the file in a matrix
  for(int i = 0; i < MAX_COL; i ++){
    for(int j = 0; j < MAX_ROW ; j++){
      if(!fscanf(a, "%d", &matrix[i][j]))
	//printf("%d", matrix[i][j]);
	break;
    }
  }
  fclose(a);

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

void export_matrix(int **matrix, int rows, int cols){
  int i, j;
  FILE *turned;
  turned = fopen("turned_pic.ppm", "w");
  printf("\n you imgae turned is in the file turned_pic.ppm : \n");
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      fprintf(turned, "%d ",  matrix[i][j]);
    }
    fprintf(turned, "\n");
  }
}

void print_matrix(int ** matrix, int rows, int cols){
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
