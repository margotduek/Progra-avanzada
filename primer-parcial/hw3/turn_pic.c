/*
Margot Duek
Turned picture
30/01/2017
Advanced programming
*/


#include <stdio.h>
#include "turn_pic.h"
#include <stdlib.h>

int main(){
  struct matrix picture;
  picture.cols = get_cols();
  picture.rows = get_rows();
  picture.mat = create_matrix(picture.rows, picture.cols);
  read_file(picture.mat, picture.cols, picture.rows);
  turn_picture(picture.mat, picture.rows, picture.cols);
  export_matrix(picture.mat, picture.rows, picture.cols);
  free_matrix(picture.mat, picture.rows);
  return 0;
}

//Function to get the columns from a ppm file
int get_cols(){
  FILE *a = fopen( "skull.ppm", "r");
  int cols;
  char buff[255];
  fgets(buff, 255, a);
  fgets(buff, 255, a);
  fscanf(a, "%s", buff);
  fscanf(a, "%s", buff);
  cols = atoi(buff);
  fclose(a);
  cols = cols*3;
  return cols;
}

//Function to get the rows from a ppm file
int get_rows(){
  FILE *a = fopen( "skull.ppm", "r");
  int rows;
  char buff[255];
  fgets(buff, 255, a);
  fgets(buff, 255, a);
  fscanf(a, "%s", buff);
  fclose(a);
  rows = atoi(buff);
  return rows;
}

//Function to read a file and store it on a matrix
void read_file(int **matrix, int cols, int rows){
  // Opening a file for reading
  FILE *a = fopen( "skull.ppm", "r");
  char buff[255];
  fgets(buff, 255, a);
  fgets(buff, 255, a);
  fgets(buff, 255, a);
  fgets(buff, 255, a);
  // saving the numbers of the file in a matrix
  for(int i = 0; i < rows; i ++){
    for(int j = 0; j < cols ; j++){
      if(!fscanf(a, "%d", &matrix[i][j]))
	break;
    }
  }
  fclose(a);

}

//Function to make the matrix dinamic
int ** create_matrix(int rows, int cols)
{
  int i;
  int ** retVal = (int **) malloc(sizeof(int *)*rows);
  for (i = 0; i < rows; i++) {
    retVal[i] = (int *) malloc(sizeof(int)*cols);
  }
  return retVal;
}


//Function to fill a matrix
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

//Function to invert the colors of a ppm picture
void turn_picture(int ** matrix, int rows, int cols){
  int i, j;
  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      matrix[i][j] = 255 - matrix[i][j];
    }
  }
}

//Function to export a mmatrix to a ppm file
void export_matrix(int **matrix, int rows, int cols){
  int i, j;
  FILE *turned;
  turned = fopen("turned_pic.ppm", "w");
  printf("\n you imgae turned is in the file turned_pic.ppm \n");
  fprintf(turned, "%s", "P3\n");
  fprintf(turned, "%s", "# n_skull-icon.ppm\n");
  fprintf(turned, "%s", "512 512\n");
  fprintf(turned, "%s", "255\n");
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      fprintf(turned, "%d ",  matrix[i][j]);
    }
    fprintf(turned, "\n");
  }
}

//Function to print the matrix on the terminal
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


//Function to free the space we alocated with create_matrix()
void free_matrix(int ** matrix, int rows)
{

    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }

  free(matrix);
}
