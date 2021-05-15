#ifndef LIB

  #include "library.h"
#endif

char is_valid_for_multiplications(Matrix mat1 , Matrix mat2);
Matrix multiply(Matrix mat1 , Matrix mat2);
void multiply_first_method(Matrix mat1 , Matrix mat2 , Matrix result);
void multiply_second_method(Matrix mat1 , Matrix mat2 , Matrix result);
int row_times_column(int ** mt1 , int **mt2 , int row , int column , int common);
void row_in_column_and_put_result(int **mat1 , int ** mat2 ,int** result, int row , int column , int common);
