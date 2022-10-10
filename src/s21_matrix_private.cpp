#include "./s21_matrix_oop.h"

/*===============================================================/
/                                                                /
/                     MATRIX++ PROJECT SCHOOL 21                 /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

void S21Matrix::create() {
  isCreated = false;
  matrix_ = new double *[rows_];
  for (int r = 0; r < rows_; r++) {
    matrix_[r] = new double[cols_];
  }
  if (matrix_ != nullptr) {
    isCreated = true;
    initZero();
  }
}

void S21Matrix::remove() {
  for (int r = 0; r < rows_; r++) {
    delete[] matrix_[r];
  }
  delete matrix_;
}

void S21Matrix::copy(const S21Matrix &other) {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      this->matrix_[r][c] = other.matrix_[r][c];
    }
  }
}

void S21Matrix::initZero() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] = 0.0;
    }
  }
}

double S21Matrix::getDeterminant(S21Matrix &other) {
  double determinant = 0.0;
  int sign = 1;
  if (other.rows_ == 1 && other.cols_ == 1) {
    determinant = other.matrix_[0][0];
  } else if (other.rows_ == 2 && other.cols_ == 2) {
    determinant = (other.matrix_[0][0] * other.matrix_[1][1]) -
                  (other.matrix_[0][1] * other.matrix_[1][0]);
  } else {
    for (int c = 0; c < other.cols_; c++) {
      S21Matrix MinorMatrix(other.rows_ - 1, other.cols_ - 1);
      other.getSmallerOrderMatrix(0, c, MinorMatrix);
      determinant += sign * other.matrix_[0][c] * getDeterminant(MinorMatrix);
      sign = -sign;
    }
  }
  return determinant;
}

void S21Matrix::getSmallerOrderMatrix(int row, int col, S21Matrix &minor) {
  int skip_row = 0;
  int skip_col = 0;
  for (int r = 0; r < minor.rows_; r++) {
    if (r == row) skip_row = 1;
    skip_col = 0;
    for (int c = 0; c < minor.cols_; c++) {
      if (c == col) skip_col = 1;
      minor.matrix_[r][c] = this->matrix_[r + skip_row][c + skip_col];
    }
  }
}

void S21Matrix::getAlgebraicAddition() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      if ((r + c) % 2 != 0) {
        matrix_[r][c] = -matrix_[r][c];
      }
    }
  }
}

double S21Matrix::calculateMinorItem(int row, int col) {
  double minor_item = 0.0;
  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
  this->getSmallerOrderMatrix(row, col, minor_matrix);
  minor_item = getDeterminant(minor_matrix);
  return minor_item;
}
