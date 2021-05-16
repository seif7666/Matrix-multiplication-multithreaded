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
/**
  Checks that column of first is equal to row of Second
**/
char is_valid_for_multiplications(Matrix mat1 , Matrix mat2);
/**
  Handle matrix multiplications for the three methods.
  Checks that they have the same result.
  Returns a full array if results are same ,
  else  it returns NULL
**/
Matrix multiply(Matrix mat1 , Matrix mat2);
/**
  Ordinary way to multiply matrices
  Result is put in result
**/
void multiply_first_method(Matrix mat1 , Matrix mat2 , Matrix result);
/**
  Perform matrix multiplication, by creating a thread for each row.
**/
void multiply_second_method(Matrix mat1 , Matrix mat2 , Matrix result);
/**
Perform matrix multiplication, by creating a thread for each element.
**/
void multiply_third_method(Matrix mat1 , Matrix mat2 , Matrix result);
/**
  Perform the multiplication between specified row and column and return result.
**/
int row_times_column(int ** mt1 , int **mt2 , int row , int column , int common);
/**
  Function called by thread, to execute second method.
**/
void* operation_per_row( void *args);

/**
  Function called by thread, to execute third method.
**/
void* row_in_column_and_put_result(struct thread_3args * args);
