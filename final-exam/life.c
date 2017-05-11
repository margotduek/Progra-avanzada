/*
Margot Duek
Final Exam
11/05/19
Advanced programming
*/


#include <stdio.h>
#include "life.h"
#include <stdlib.h>

#define BUFFER_SIZE 255

int image_counter = 0;

int main(int argc, char **argv){
  //Recieves the name of the file as an argument
	char * fileName = argv[2];
  //Recives the number of iterations
  int noiterations = atoi(argv[1]);
  struct matrix life;
  struct matrix game;
  //We get the columns, the rows, create the matrix and fill the matrix with the text
  life.cols = get_cols(fileName);
  life.rows = get_rows(fileName);
  life.mat = create_matrix(life.rows, life.cols);
  game.mat = create_matrix(life.rows, life.cols);
  read_file(life.mat,life.cols, life.rows, fileName);
  read_file(game.mat,life.cols, life.rows, fileName);

  //We repet this the time of iterations the user asked for
  for (int i = 0; i < noiterations; i++) {
    //Make the game of life and put it into matrix game
    game_of_life(life.mat,  game.mat, life.rows, life.cols);
    //Export the matrix to a pgm file
    export_matrix(game.mat, life.rows, life.cols);
    //Put the new values to the matrix so that the next iteration starts from the lastone
    matrix_to_new(life.mat,  game.mat, life.rows, life.cols);
  }
  //If you want to print the matrix in "1" and "0" uncomente the following two lines
  //print_matrix(life.mat, life.rows, life.cols);
  //print_matrix(game.mat, life.rows, life.cols);
  return 0;
}


//Function to get the columns from a ppm file
int get_cols(char * file){
  //open the file for reading purpuses
  FILE *a = fopen( file, "r");
  int cols;
  char buff[255];
  // get the value of the columns as a string
  fscanf(a, "%s", buff);
  fscanf(a, "%s", buff);
  //cast the values to int
  cols = atoi(buff);
  fclose(a);
  cols = cols;
  return cols;
}

//Function to get the rows from a ppm file
int get_rows(char * file){
  //open the file for reading purpuses
  FILE *a = fopen( file, "r");
  int rows;
  char buff[255];
  // get the value of the rows as a string
  fscanf(a, "%s", buff);
  fclose(a);
  //cast the values to int
  rows = atoi(buff);
  return rows;
}

//Function to read a file and store it on a matrix
void read_file(int **matrix, int cols, int rows, char * file){
  // Opening a file for reading
  FILE *a = fopen( file, "r");
  char buff[255];
  fgets(buff, 255, a);
  // saving the numbers of the file in a matrix
  for(int i = 0; i < rows; i ++){
    for(int j = 0; j < cols ; j++){
      if(!fscanf(a, "%d", &matrix[i][j])){
	     break;
     }
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
  for (i=0; i<rows; i++){
    for (j=0; j<cols; j++){
	     matrix[i][j] = data++;
	  }
  }
}

//Function to iterate in the game
void game_of_life(int ** matrix, int ** game,  int rows, int cols){
  int i, j;
  int lbits = 0;

  //Paralelize the for so that we can have a better performance
  #pragma omp parallel for default(none), private(j, cols), shared(matrix, game, lbits , rows, i)
  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      //there are 8 ifs to check how many neibourrs are alive
      if(i > 0 && j > 0 && matrix[i-1][j-1] == 1){
        lbits++;
      }
       if(i > 0 && matrix[i-1][j] == 1){
        lbits++;
      }
       if(i > 0 && j < cols - 1 && matrix[i-1][j+1] == 1){
        lbits++;
      }
       if(j > 0 && matrix[i][j-1] == 1){
        lbits++;
      }
       if(j > 0 && i < rows - 1 && matrix[i+1][j-1] == 1){
        lbits++;
      }
       if(j < cols - 1 && matrix[i][j+1] == 1){
        lbits++;
      }
       if(j < cols - 1 && i < rows - 1 && matrix[i+1][j+1] == 1){
        lbits++;
      }
       if( i < rows - 1 && matrix[i+1][j] == 1){
        lbits++;
      }
      //We change the number to 1 or to 0 depending on the rules of the game
      if (matrix[i][j] == 1 && lbits < 2) {
        game[i][j] = 0;
      }else if(matrix[i][j] == 1 && lbits > 3){
        game[i][j] = 0;
      }else if(matrix[i][j] == 0 && lbits == 3){
        game[i][j] = 1;
      }
      lbits = 0;
    }
  }
}

//Function to print the matrix on the terminal
void print_matrix(int ** matrix, int rows, int cols){
  int i, j;

  for (i=0; i<rows; i++){
    for (j=0; j<cols; j++){
	     printf("%d", matrix[i][j]);
	    }
      printf("\n");
    }
  printf("\n");
}



//Function to export a mmatrix to a ppm file
void export_matrix(int **matrix, int rows, int cols){
  int i, j;
  FILE *game;
  // declare the name of the file as a number so that we can wave as many files as iterations we make
  char cated_string[BUFFER_SIZE];
  char ext[] = ".pgm";
  sprintf(cated_string,"%d%s",image_counter,ext);
  game = fopen(cated_string, "w");

  //we write the pgm file with the game of life
  fprintf(game, "%s", "P2\n");
  fprintf(game, "%s", "# iteration.pgm\n");
  fprintf(game, "%d %d", rows, cols);
  fprintf(game, "%s", "\n255\n");
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      if(matrix[i][j] == 1){
        fprintf(game, "%d ", 255 );
      }else{
        fprintf(game, "%d ", 0 );
      }
    }
    fprintf(game, "\n");
  }
  image_counter ++;
}

//Function to copy the matrix
void matrix_to_new (int ** matrix, int ** game, int rows, int cols){
  int i, j;
  int data = 1;
  for (i=0; i<rows; i++){
    for (j=0; j<cols; j++){
       matrix[i][j] = game[i][j];
    }
  }
}
