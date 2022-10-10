#include "./s21_matrix_oop.h"

/*===============================================================/
/                                                                /
/                     MATRIX++ PROJECT SCHOOL 21                 /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

/**
 * @brief Стандартный конструктор без входных параметров.
 * Создает матрицу 3 на 3 и заполняет её нулями
 */
S21Matrix::S21Matrix() : rows_(3), cols_(3) { create(); }

/**
 * @brief Конструктор с двумя входными параметрами.
 * Создает матрицу со сторонами rows на cols
 * @param rows количество строк в матрице
 * @param cols количество столбцов в матрице
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::bad_array_new_length();
  } else {
    create();
  }
}

/**
 * @brief Конструктор копирования.
 * Копирует все данные матрицы other в текущую матрицу
 * @param other матрица с которой будут браться данные
 */
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  create();
  copy(other);
}

/**
 * @brief Конструктор переноса.
 * Переопределяет указатель текущей матрицы на данные матрицы other.
 * Приводит матрицу other к стандартному после этого переопределения состоянию
 * @param other матрица с которой будет совершен перенос
 */
S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

/**
 * @brief Деструктор класса S21Matrix
 *
 */
S21Matrix::~S21Matrix() {
  if (isCreated) {
    remove();
  }
}

/**
 * @brief Функция сравнивает текущую матрицу и матрицу other
 * между собой
 * @param other матрица для сравнения с текущей
 * @return true - если матрицы равны, false - если не равны
 */
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool equal = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    bool check = true;
    for (int r = 0; r < rows_ && check; r++) {
      for (int c = 0; c < cols_; c++) {
        if (fabs(matrix_[r][c] - other.matrix_[r][c]) >= 1e-6) {
          equal = false;
          check = false;
        }
      }
    }
  }
  return equal;
}

/**
 * @brief Функция суммирует текущую матрицу и матрицу other.
 * Результат сложения будет записан в текущую матрицу
 * @param other матрица для сложения с текущей
 */
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("SumMatrix: Sizes of matrices are not the same!");
  } else {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        matrix_[r][c] += other.matrix_[r][c];
      }
    }
  }
}

/**
 * @brief Функция находит разницу текущей матрицы и матрицы other.
 * Результат разницы будет записан в текущую матрицу
 * @param other матрица для вычитания с текущей
 */
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("SubMatrix: Sizes of matrices are not the same!");
  } else {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        matrix_[r][c] -= other.matrix_[r][c];
      }
    }
  }
}

/**
 * @brief Функция умножает текущую матрицу на 'num'.
 * Результат умножения будет записан в текущую матрицу
 * @param num число на которое будет умножена матрица
 */
void S21Matrix::MulNumber(const double num) {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] *= num;
    }
  }
}

/**
 * @brief Функция умножает текущую матрицу на матрицу other.
 * Результат умножения будет записан в текущую матрицу
 * @param other матрица для умножения с текущей
 */
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Columns of first matrix is not equal"
        "to rows of second matrix!");
  } else {
    S21Matrix tmp_this(*this);
    this->remove();
    this->rows_ = tmp_this.rows_;
    this->cols_ = other.cols_;
    this->create();

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        for (int k = 0; k < other.rows_; k++) {
          matrix_[i][j] += tmp_this.matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
  }
}

/**
 * @brief Функция транспонирует текущую матрицу
 * @return Транспонированную матрицу текущей матрицы
 */
S21Matrix S21Matrix::Transpose() {
  S21Matrix Transpose_this(cols_, rows_);
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      Transpose_this.matrix_[c][r] = this->matrix_[r][c];
    }
  }
  return Transpose_this;
}

/**
 * @brief Функция считает матрицу алгебраических дополнений текущей матрицы
 * @return Матрицу алгебраических дополнений
 */
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range("CalcComplements: Matrix is not a square!");
  } else {
    S21Matrix CalcComplementMatrix(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        CalcComplementMatrix.matrix_[r][c] = this->calculateMinorItem(r, c);
      }
    }
    CalcComplementMatrix.getAlgebraicAddition();
    return CalcComplementMatrix;
  }
}

/**
 * @brief Функция считает определитель текущей матрицы
 * @return определитель матрицы в типе double
 */
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range("Determinant: Matrix is not a square!");
  } else {
    double determinant = getDeterminant(*this);
    return determinant;
  }
}

/**
 * @brief Функция считает обратную матрицу текущей матрицы
 * @return Обратную матрицу текущей матрицы
 */
S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (determinant == 0.0) {
    throw std::out_of_range("InverseMatrix: Matrix determinant is zero!");
  } else {
    S21Matrix InverseMatrix((this->CalcComplements()).Transpose());
    InverseMatrix.MulNumber(1 / fabs(determinant));
    return InverseMatrix;
  }
}

/**
 * @brief Функция изменяет количество столбцов текущей матрицы.
 * Все значения сохраняются. Если количетсво столбцов будет больше
 * то новые столбцы будут заполнены нулями. Если количество столбцов будет
 * меньше то текущая матрица будет просто обрезана
 * @param cols новое количество столбцов в текущей матрице
 */
void S21Matrix::setCol(int cols) {
  if (cols <= 0) {
    throw std::out_of_range("setCol: 'cols' element less or equal zero!");
  } else {
    S21Matrix tmp_this(*this);
    remove();
    cols_ = cols;
    create();
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        if (c < tmp_this.cols_) {
          matrix_[r][c] = tmp_this.matrix_[r][c];
        }
      }
    }
  }
}

/**
 * @brief Функция изменяет количество строк текущей матрицы.
 * Все значения сохраняются. Если количетсво строк будет больше
 * то новые строки будут заполнены нулями. Если количество строк будет меньше
 * то текущая матрица будет просто обрезана
 * @param rows новое количество строк в текущей матрице
 */
void S21Matrix::setRow(int rows) {
  if (rows <= 0) {
    throw std::out_of_range("setRow: 'rows' element less or equal zero!");
  } else {
    S21Matrix tmp_this(*this);
    remove();
    rows_ = rows;
    create();
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        if (r < tmp_this.rows_) {
          matrix_[r][c] = tmp_this.matrix_[r][c];
        }
      }
    }
  }
}
