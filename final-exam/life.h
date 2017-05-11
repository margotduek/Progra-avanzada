/*
Margot Duek
Final Exam
11/05/17
Advanced programming
*/

#include <string.h>

struct matrix{
  int rows;
  int cols;
  int **mat;
};

//Function to make the matrix dinamic
int **create_matrix(int rows, int columns);
//Function to free the space we alocated with create_matrix()
void free_matrix(int **picture, int rows);
//Function to fill a matrix
void fillRandomMatrix(int ** matrix, int rows, int cols);
//Function to print the matrix on the terminal
void print_matrix(int ** matrix, int rows, int cols);
//Function to read a file and store it on a matrix
void read_file(int **matrix, int cols, int rows, char * file);
//Function to export a mmatrix to a ppm file
void export_matrix(int **matrix, int rows, int cols);
//Function to get the columns from a ppm file
int get_cols(char * file);
//Function to get the rows from a ppm file
int get_rows(char * file);
//Function to iterate in the game
void game_of_life(int ** matrix, int ** game, int rows, int cols);
//Function to copy the matrix
void matrix_to_new (int ** matrix, int ** game, int rows, int cols);
