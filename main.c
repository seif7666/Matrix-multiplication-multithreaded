#include "library.h"
#include "mat_operations.h"
#define PATH_SIZE 25

const char* def_path1 = "a.txt";
const char* def_path2 = "b.txt";
const char* def_path3 = "c.out";

int main(int argc , char *argv[]){
  char path1[PATH_SIZE],path2[PATH_SIZE] , path3[PATH_SIZE];
  if (argc !=4){
    strcpy(path1 , def_path1);
    strcpy(path2 , def_path2);
    strcpy(path3 , def_path3);
  }
  else{
    strcpy(path1 , argv[1]);
    strcpy(path2 , argv[2]);
    strcpy(path3 , argv[3]);
  }

  int **matrix1 , **matrix2;
  Matrix mat1 , mat2;

  mat1=read_matrix(path1 , &matrix1);
  mat2=read_matrix(path2 , &matrix2);

  if( ! is_valid_for_multiplications(mat1 , mat2)){
    printf("Invalid bounds!\n");
    return -1;
  }
  Matrix result=multiply(mat1 , mat2);
  write_matrix_to_file(result.array ,result.row , result.column , path3);
  printf("Results are written to path %s\n", path3);
  return 0;
}
