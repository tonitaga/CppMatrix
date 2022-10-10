#include "./s21_matrix_oop.h"

/*===============================================================/
/                                                                /
/                     MATRIX++ PROJECT SCHOOL 21                 /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("operator+ : Sizes of matrices are not the same!");
  } else {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        result.matrix_[r][c] = this->matrix_[r][c] + other.matrix_[r][c];
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("operator+ : Sizes of matrices are not the same!");
  } else {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        result.matrix_[r][c] = this->matrix_[r][c] - other.matrix_[r][c];
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(rows_, other.cols_);
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Columns of first matrix is not equal"
        "to rows of second matrix!");
  } else {
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        for (int k = 0; k < other.rows_; k++) {
          result.matrix_[i][j] = this->matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(rows_, cols_);
  result.copy(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  remove();
  rows_ = other.rows_, cols_ = other.cols_;
  create();
  copy(other);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  this->MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if ((row >= rows_ || row < 0) || (col >= cols_ || col < 0)) {
    throw std::out_of_range("Row or Col number out of size of matrix!");
  } else {
    return matrix_[row][col];
  }
}
