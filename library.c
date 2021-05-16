#include "library.h"
#define SIZE 30


// int get_size(char *path){
//   FILE *fp = fopen(path , "r");
//
//
// }
//row=10 col=5
Matrix read_matrix(char *path , int ***matrix){
  FILE *fp = fopen(path , "r");
  if(fp == NULL){
    printf("Path %s Was not found!!\n",path );
    exit(-1);
  }
  char rows[SIZE] , columns[SIZE];
  fscanf(fp , "%s" , rows);
  fscanf(fp , "%s" , columns);
  // printf("ROWS: %s\n",rows );
  // printf("COLUMNS: %s\n",columns );

  int rows_num = get_number(rows);
  int columns_num = get_number(columns);
  // printf("Rows is %d\n",rows_num );
  // printf("Columns is %d\n",columns_num );
  *matrix = (int**)calloc(rows_num , sizeof(int*));
  for(int i = 0 ;i<rows_num ; i++){
    int *ptr = (int*)calloc(columns_num , sizeof(int));
    (*matrix)[i] = ptr;
  }

  read_matrix_elements(fp , *matrix , rows_num , columns_num);

  fclose(fp);
  Matrix mat;
  mat.array = *matrix;
  mat.row = rows_num;
  mat.column = columns_num;

  // print_matrix(mat);
  return mat;
}

void read_matrix_elements(FILE *fp , int ** matrix , int rows , int cols){

  for (int i = 0 ; i<rows ; i++){
    for (int j = 0 ; j<cols ; j++){
      char buffer[5];
      fscanf(fp , "%s" , buffer);
      // printf("Buffer is %s\n",buffer );
      matrix[i][j] = get_number_from_str(buffer);
    }

  }
}

void write_matrix_to_file(int **result,int row,int column , char*path){

  FILE *fp = fopen(path , "w");
  for(int i = 0 ; i<row;i++){
    for(int j = 0 ; j<column ; j++){
       fprintf(fp,"%d\t",result[i][j]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}

int get_number(char *str){
  char *ptr = str;
  // printf("%c\n",*ptr);
  while(*ptr != '='){
    ptr++;
  }
  ptr++;

  return get_number_from_str(ptr);
}

void print_array(int **matrix , int rows , int cols){
  printf("Rows is %d\t columns is %d\n",rows,cols );

  for (int i = 0 ; i<rows; i++){
    for (int j = 0 ; j<cols; j++)
      printf("%d\t",matrix[i][j]);
    printf("\n");
  }
}

  int get_number_from_str(char *ptr){
    int number = 0;
    while (*ptr != 0){
      number = number*10 + (int)(*ptr - '0');
      ptr++;
    }
    return number;
  }

  void print_matrix(Matrix matrix){
    print_array(matrix.array , matrix.row , matrix.column);
  }
