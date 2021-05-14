#define LIB
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Matrix{
  int ** array;
  int row;
  int column;
}Matrix;

Matrix read_matrix(char *path , int ***matrix);
void read_matrix_elements(FILE * , int ** , int rows , int columns);
int get_number(char *);
int get_number_from_str(char *);
void print_array(int** , int , int);
void print_matrix(Matrix matrix);
