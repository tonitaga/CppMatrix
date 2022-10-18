#ifndef SRC_S21_MATRIX_OOP_H
#define SRC_S21_MATRIX_OOP_H

/*===============================================================/
/                                                                /
/                     MATRIX++ PROJECT SCHOOL 21                 /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  /*
      Конструкторы и деструктор класса S21Matrix
  */

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  /*
      Блок доступа к приватным значениям
      количества строк и столбцов с возможностью
      их изменения
  */

  int GetCol() const { return cols_; }
  int GetRow() const { return rows_; }
  void SetCol(int cols);
  void SetRow(int rows);

  /*
      Блок методов класса S21Matrix занимающихся
      стандартными оцерациями над матрицами
  */

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  /*
      Блок операторов класса S21Matrix занимающиеся
      стандартными операциями над матрицами
  */

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  double &operator()(int row, int col);
  double operator()(int row, int col) const;

 private:
  /*
      Основные приватные поля класса S21Matrix
  */

  int rows_;
  int cols_;
  double **matrix_;

  /*
      Приватные-support поля класса S21Matrix
  */

  bool isCreated;

  /*
      Блок приватных-support методов класса S21Matrix
  */

  void Create();
  void Remove();
  void Copy(const S21Matrix &other);
  double GetDeterminant(S21Matrix &other);
  void MakeSmallerOrderMatrix(int row, int col, S21Matrix &minor);
  double CalculateMinorItem(int row, int col);
  void MakeAlgebraicAddition();
};

#endif  // !SRC_S21_MATRIX_OOP_H
