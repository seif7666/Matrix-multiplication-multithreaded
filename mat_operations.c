#include "mat_operations.h"

struct timeval stop, start;


char is_valid_for_multiplications(Matrix mat1 , Matrix mat2){
      return mat1.column == mat2.row;
}

Matrix multiply(Matrix mat1 , Matrix mat2){
  Matrix result;
  result.row = mat1.row;
  result.column = mat2.column;
  result.array = calloc(result.row , sizeof(int*));
  for(int i = 0 ; i<result.row ; i++)
    result.array[i] = calloc(result.column , sizeof(int));

  // gettimeofday(&start, NULL); //start checking time

  // multiply_first_method(mat1 , mat2 , result);
  // gettimeofday(&stop, NULL); //end checking time
  // printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
  // printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
  // print_matrix(result);
  multiply_second_method(mat1 , mat2 , result);
  // multiply_third_method(mat1 , mat2 , result);
}

void multiply_first_method(Matrix mat1 , Matrix mat2 , Matrix result){
  for(int i =0;i<result.row ; i++){
    for(int j = 0 ;j<result.column ; j++){
        result.array[i][j] = row_times_column(mat1.array , mat2.array , i , j , mat1.column);
    }
  }
}

void multiply_second_method(Matrix mat1 , Matrix mat2 , Matrix result){

  pthread_t thread_ids[result.row];
	printf("Before Thread\n");
  // const char *x = "Hello";
	// pthread_create(&thread_id, NULL, myThreadFun, (void*)x);
	// pthread_join(thread_id, NULL);
  struct thread_2Args *args;
  for(int i =0;i<result.row ; i++){
    args = (struct thread_2Args*)malloc(sizeof(struct thread_2Args));
    args->mt1 = mat1;
    args->mt2 = mat2;
    args->result = result;
    args->row = i;
    pthread_create(&(thread_ids[i]) , NULL , operation_per_row ,(void*)args);
  }
  for(int i = 0 ;i<result.row ; i++){
    pthread_join(thread_ids[i], NULL);
  }
  print_matrix(result);
}

void * operation_per_row(void *args){

  for(int j = 0 ; j<((struct thread_2Args *)args)->result.column ; j++)
    ((struct thread_2Args *)args)->result.array[((struct thread_2Args *)args)->row][j] =
     row_times_column(
       ((struct thread_2Args *)args)->mt1.array ,
     ((struct thread_2Args *)args)->mt2.array ,
      ((struct thread_2Args *)args)->row ,
       j ,
       ((struct thread_2Args *)args)->mt1.column
     );
  free(args);
}

void row_in_column_and_put_result(int **mat1 , int ** mat2 ,int** result, int row , int column , int common){
  result[row][column] = row_times_column(mat1 , mat2 , row , column , common);
}

int row_times_column(int ** mt1 , int **mt2 , int row , int column , int common){
  int result = 0;
  for(int c = 0 ;c<common ; c++)
    result += mt1[row][c] * mt2[c][column];
  return result;
}
