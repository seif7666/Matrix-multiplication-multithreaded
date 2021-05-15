#ifndef LIB
  #include "library.h"
#endif
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <sys/time.h>
#include <pthread.h>


struct thread_2Args{
  Matrix mt1 ;
  Matrix mt2 ;
  Matrix result ;
  int row;
};

struct thread_3args{
  int **mat1;
  int **mat2;
  int **result;
  int row;
  int column;
  int common;
};

char is_valid_for_multiplications(Matrix mat1 , Matrix mat2);
Matrix multiply(Matrix mat1 , Matrix mat2);
void multiply_first_method(Matrix mat1 , Matrix mat2 , Matrix result);
void multiply_second_method(Matrix mat1 , Matrix mat2 , Matrix result);
void multiply_third_method(Matrix mat1 , Matrix mat2 , Matrix result);
int row_times_column(int ** mt1 , int **mt2 , int row , int column , int common);
void* operation_per_row( void *args);
void* row_in_column_and_put_result(struct thread_3args * args);
