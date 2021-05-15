#include "mat_operations.h"

struct timeval stop, start;


char is_valid_for_multiplications(Matrix mat1 , Matrix mat2){
      return mat1.column == mat2.row;
}

Matrix multiply(Matrix mat1 , Matrix mat2){
  Matrix results[3]; // 3 copies to check that solution is correct.
  for(int m = 0 ;m<3 ;m++){
    results[m].row = mat1.row;
    results[m].column = mat2.column;
    results[m].array = calloc(results[m].row , sizeof(int*));
    for(int i = 0 ; i<results[m].row ; i++)
      results[m].array[i] = calloc(results[m].column , sizeof(int));
  }

  gettimeofday(&start, NULL); //start checking time
  multiply_first_method(mat1 , mat2 , results[0]);
  gettimeofday(&stop, NULL); //end checking time
  printf("Microseconds taken first method: %lu\n", stop.tv_usec - start.tv_usec);

  gettimeofday(&start, NULL); //start checking time
  multiply_second_method(mat1 , mat2 , results[1]);
  gettimeofday(&stop, NULL); //end checking time
  printf("Microseconds taken Second method: %lu\n", stop.tv_usec - start.tv_usec);

  gettimeofday(&start, NULL); //start checking time
  multiply_third_method(mat1 , mat2 , results[2]);
  gettimeofday(&stop, NULL); //end checking time
  printf("Microseconds taken Third method: %lu\n", stop.tv_usec - start.tv_usec);

  for(int i = 0 ;i<mat1.row ; i++)
    for(int j = 0;j<mat2.column ; j++){
      if(results[0].array[i][j] != results[1].array[i][j] || results[0].array[i][j] != results[2].array[i][j]){
        printf("Not equal!!!\n" );
        free(results[0].array);
        free(results[1].array);
        free(results[2].array);
        results[0].array = NULL;
        return results[0];
      }
    }
  free(results[1].array);
  free(results[2].array);
  return results[0];
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
}

void multiply_third_method(Matrix mat1 , Matrix mat2 , Matrix result){
  pthread_t thread_ids[result.row][result.column];
  struct thread_3args *args;

  for(int i = 0 ; i<result.row ; i++)
    for(int j = 0;j<result.column ; j++){
      args = (struct thread_3args*)malloc(sizeof(struct thread_3args));
      args->mat1 = mat1.array;
      args->mat2 = mat2.array;
      args->result = result.array;
      args->row = i;
      args->column = j;
      args->common = mat1.column;
      pthread_create(&(thread_ids[i][j]) , NULL ,row_in_column_and_put_result, (void*)args);
    }
    for(int i = 0 ; i<result.row ; i++)
      for(int j = 0;j<result.column ; j++){
        pthread_join(thread_ids[i][j] , NULL);
      }
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

int row_times_column(int ** mt1 , int **mt2 , int row , int column , int common){
  int result = 0;
  for(int c = 0 ;c<common ; c++)
    result += mt1[row][c] * mt2[c][column];
  return result;
}

void* row_in_column_and_put_result(struct thread_3args *args){
  args->result[args->row][args->column] = row_times_column(args->mat1 , args->mat2 , args->row , args->column , args->common);
  free(args);
}
