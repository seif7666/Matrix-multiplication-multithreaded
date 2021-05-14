#include "mat_operations.h"


char is_valid_for_multiplications(Matrix mat1 , Matrix mat2){
      return mat1.column == mat2.row;
}

// Matrix multiply
