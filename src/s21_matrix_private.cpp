#include "./s21_matrix_oop.h"

/*===============================================================/
/                                                                /
/                     MATRIX++ PROJECT SCHOOL 21                 /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

void S21Matrix::Create() {
  isCreated = false;
  matrix_ = new double *[rows_]();
  for (int row = 0; row < rows_; row++) {
    matrix_[row] = new double[cols_]();
  }
  if (matrix_ != nullptr) {
    isCreated = true;
  }
}

void S21Matrix::Remove() {
  for (int row = 0; row < rows_; row++) {
    delete[] matrix_[row];
  }
  delete[] matrix_;
  rows_ = cols_ = 0;
}

void S21Matrix::Copy(const S21Matrix &other) {
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = other(row, col);
    }
  }
}

double S21Matrix::GetDeterminant(S21Matrix &other) {
  double determinant = 0.0;
  int sign = 1;
  if (other.GetRow() == 1 && other.GetCol() == 1) {
    determinant = other(0, 0);
  } else if (other.rows_ == 2 && other.cols_ == 2) {
    determinant = (other(0, 0) * other(1, 1)) - (other(0, 1) * other(1, 0));
  } else {
    for (int col = 0; col < other.GetCol(); col++) {
      S21Matrix MinorMatrix(other.GetRow() - 1, other.GetCol() - 1);
      other.MakeSmallerOrderMatrix(0, col, MinorMatrix);
      determinant += sign * other(0, col) * GetDeterminant(MinorMatrix);
      sign = -sign;
    }
  }
  return determinant;
}

void S21Matrix::MakeSmallerOrderMatrix(int skipping_row, int skipping_col,
                                       S21Matrix &minor) {
  int skip_row_status = 0;
  int skip_col_status = 0;
  for (int row = 0; row < minor.GetRow(); row++) {
    if (row == skipping_row) {
      skip_row_status = 1;
    }
    skip_col_status = 0;
    for (int col = 0; col < minor.GetCol(); col++) {
      if (col == skipping_col) {
        skip_col_status = 1;
      }
      minor(row, col) = matrix_[row + skip_row_status][col + skip_col_status];
    }
  }
}

void S21Matrix::MakeAlgebraicAddition() {
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if ((row + col) % 2 != 0) {
        matrix_[row][col] = -matrix_[row][col];
      }
    }
  }
}

double S21Matrix::CalculateMinorItem(int row, int col) {
  double minor_item = 0.0;
  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
  this->MakeSmallerOrderMatrix(row, col, minor_matrix);
  minor_item = GetDeterminant(minor_matrix);
  return minor_item;
}
