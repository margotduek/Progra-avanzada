/*
Margot Duek 
Turned picture
30/01/2017
Advanced programming
*/

#include <string.h>

struct matrix{
  int rows;
  int cols;
  int ** mat = NULL;
};

int **create_matrix(int rows, int columns); 
void free_matrix(int **picture, int rows);
void fillRandomMatrix(int ** matrix, int rows, int cols);
void print_matrix(int ** matrix, int rows, int cols);
void turn_picture(int ** matrix, int rows, int cols);
void read_file(int **matrix, int cols, int rows);
void export_matrix(int **matrix, int rows, int cols);
int get_cols(int **matrix);
int get_rows(int **matrix);
