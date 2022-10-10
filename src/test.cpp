#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(EqMatrixTest, HanglesInitedEqualMatrices) {
  S21Matrix A;
  /*   Initialize   */
  A(0, 0) = 1.12345, A(0, 1) = 1.12346, A(0, 2) = 1.12347;
  A(1, 0) = 2.12345, A(1, 1) = 2.12346, A(1, 2) = 2.12347;
  A(2, 0) = 3.12345, A(2, 1) = 3.12346, A(2, 2) = 3.12347;

  S21Matrix B = A;
  bool result = A.EqMatrix(B);
  ASSERT_EQ(true, result);
}

TEST(EqMatrixTest, HanglesInitedUnEqualMatrices) {
  S21Matrix A;
  /*   Initialize   */
  A(0, 0) = 1.12345, A(0, 1) = 1.12346, A(0, 2) = 1.12347;
  A(1, 0) = 2.12345, A(1, 1) = 2.12346, A(1, 2) = 2.12347;
  A(2, 0) = 3.12345, A(2, 1) = 3.12346, A(2, 2) = 3.12347;

  S21Matrix B = A;
  B(1, 1) = 0;
  bool result = A.EqMatrix(B);
  ASSERT_EQ(false, result);
}

TEST(SumMatrixTest, HanglesInitedMatrices) {
  S21Matrix A(2, 2);
  /*   Initialize   */
  A(0, 0) = 2, A(0, 1) = 2;
  A(1, 0) = 4, A(1, 1) = 4;

  S21Matrix B = A * 2;
  A.SumMatrix(A);
  ASSERT_EQ(true, A.EqMatrix(B));
}

TEST(SubMatrixTest, HanglesInitedMatrices) {
  S21Matrix A(2, 2);
  /*   Initialize   */
  A(0, 0) = 2, A(0, 1) = 2;
  A(1, 0) = 4, A(1, 1) = 4;

  S21Matrix B(2, 2);
  A.SubMatrix(A);
  ASSERT_EQ(true, A.EqMatrix(B));
}

TEST(MulMatrixTest, HanglesInitedMatrices) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  /*   Initialize   */
  int k = 1;
  for (int i = 0; i < A.getRow(); i++) {
    for (int j = 0; j < A.getCol(); j++) {
      A(i, j) = k++;
    }
  }
  k = 0;
  for (int i = 0; i < B.getRow(); i++) {
    for (int j = 0; j < B.getCol(); j++) {
      B(i, j) = k;
      k += 2;
    }
  }
  A.MulMatrix(B);
  S21Matrix R(3, 3);
  /*   Initialize   */
  R(0, 0) = 12, R(0, 1) = 18, R(0, 2) = 24;
  R(1, 0) = 24, R(1, 1) = 38, R(1, 2) = 52;
  R(2, 0) = 36, R(2, 1) = 58, R(2, 2) = 80;
  ASSERT_EQ(true, A.EqMatrix(R));
}

TEST(MulNumberTest, HanglesInitedMatrices) {
  S21Matrix A;
  /*   Initialize   */
  for (int i = 0; i < A.getRow(); i++) {
    for (int j = 0; j < A.getCol(); j++) {
      A(i, j) = 1 + std::rand() % 10;
    }
  }
  S21Matrix B = A * 2;
  A.MulNumber(2);
  ASSERT_EQ(true, A.EqMatrix(B));
}

TEST(TransposeTest, HanglesInitedMatrices) {
  S21Matrix A(2, 3);
  /*   Initialize   */
  int k = 0;
  for (int i = 0; i < A.getRow(); i++) {
    for (int j = 0; j < A.getCol(); j++) {
      A(i, j) = k++;
    }
  }
  S21Matrix C = A.Transpose();
  S21Matrix B(3, 2);
  /*   Initialize   */
  B(0, 0) = 0, B(0, 1) = 3;
  B(1, 0) = 1, B(1, 1) = 4;
  B(2, 0) = 2, B(2, 1) = 5;
  ASSERT_EQ(true, B.EqMatrix(C));
}

TEST(CalcComplementsTest, HanglesInitedMatrices) {
  S21Matrix A;
  /*   Initialize   */
  A(0, 0) = 1.0, A(0, 1) = 2.0, A(0, 2) = 3.0;
  A(1, 0) = 0.0, A(1, 1) = 4.0, A(1, 2) = 2.0;
  A(2, 0) = 5.0, A(2, 1) = 2.0, A(2, 2) = 1.0;

  S21Matrix B = A.CalcComplements();
  /*   Initialize   */
  A(0, 0) = 0.0, A(0, 1) = 10.0, A(0, 2) = -20.0;
  A(1, 0) = 4.0, A(1, 1) = -14.0, A(1, 2) = 8.0;
  A(2, 0) = -8.0, A(2, 1) = -2.0, A(2, 2) = 4.0;
  ASSERT_EQ(true, A.EqMatrix(B));
}

TEST(DeterminantTest, HanglesInitedMatrices3xx3) {
  S21Matrix A(3, 3);
  /*   Initialize   */
  A(0, 0) = 1.38, A(1, 0) = -6.7, A(2, 0) = 12.5;
  A(0, 1) = 5.2, A(1, 1) = -7.9, A(2, 1) = 13.7;
  A(0, 2) = 1.3, A(1, 2) = 8.976, A(2, 2) = 2.34;

  /* |A| = 478.802664 */
  ASSERT_DOUBLE_EQ(A.Determinant(), 478.802664);
}

TEST(DeterminantTest, HanglesInitedMatrices4x4) {
  S21Matrix A(4, 4);
  /*   Initialize   */
  A(0, 0) = 1.2, A(1, 0) = 10.2, A(2, 0) = 5.8, A(3, 0) = 2.6;
  A(0, 1) = 4.8, A(1, 1) = -6.7, A(2, 1) = 3.45, A(3, 1) = -8.9;
  A(0, 2) = -3.2, A(1, 2) = 1.9, A(2, 2) = -7.8, A(3, 2) = 2.2;
  A(0, 3) = 9.08, A(1, 3) = 9.1, A(2, 3) = 0.34, A(3, 3) = -1.5;

  /* |A| = 3976.58848 */
  ASSERT_DOUBLE_EQ(A.Determinant(), 3976.58848);
}

TEST(DeterminantTest, HanglesInitedMatrices3x3) {
  S21Matrix A(3, 3);
  /*   Initialize   */
  A(0, 0) = 2, A(0, 1) = 3.4, A(0, 2) = 87.1;
  A(1, 0) = -1.9, A(1, 1) = 3.8, A(1, 2) = -3;
  A(2, 0) = 9.5, A(2, 1) = -5.6, A(2, 2) = 4;

  /* |A| =  -2291.826*/
  ASSERT_DOUBLE_EQ(A.Determinant(), -2291.826);
}

TEST(InverseMatrixTest, HanglesInitedMatrices3x3) {
  S21Matrix A(3, 3);
  /*   Initialize   */
  A(0, 0) = 1, A(0, 1) = 3, A(0, 2) = 6;
  A(1, 0) = 2, A(1, 1) = 5, A(1, 2) = 8;
  A(2, 0) = 3, A(2, 1) = 9, A(2, 2) = 9;

  A = A.InverseMatrix();
  S21Matrix B(3, 3);
  /*   Initialize   */
  B(0, 0) = -3, B(0, 1) = 3, B(0, 2) = -2 / 3.0;
  B(1, 0) = 2 / 3.0, B(1, 1) = -1, B(1, 2) = 4 / 9.0;
  B(2, 0) = 1 / 3.0, B(2, 1) = 0, B(2, 2) = -1 / 9.0;
  ASSERT_EQ(true, B.EqMatrix(A));
}

TEST(OperatorEqual, HanglesInitedMatrices) {
  S21Matrix A(4, 4);
  /*   Initialize   */
  A(0, 0) = 1.2, A(1, 0) = 10.2, A(2, 0) = 5.8, A(3, 0) = 2.6;
  A(0, 1) = 4.8, A(1, 1) = -6.7, A(2, 1) = 3.45, A(3, 1) = -8.9;
  A(0, 2) = -3.2, A(1, 2) = 1.9, A(2, 2) = -7.8, A(3, 2) = 2.2;
  A(0, 3) = 9.08, A(1, 3) = 9.1, A(2, 3) = 0.34, A(3, 3) = -1.5;
  S21Matrix B(A);
  bool eq = false;
  if (A == B) {
    eq = true;
  }
  A *B;
  ASSERT_EQ(true, eq);
}

TEST(OpetatorCopy, HanglesInitedMatrices) {
  S21Matrix A(3, 3);
  /*   Initialize   */
  A(0, 0) = 1, A(0, 1) = 3, A(0, 2) = 6;
  A(1, 0) = 2, A(1, 1) = 5, A(1, 2) = 8;
  A(2, 0) = 3, A(2, 1) = 9, A(2, 2) = 9;
  S21Matrix B;
  B = A;
  ASSERT_EQ(true, B.EqMatrix(A));
}

TEST(OpetatorSum, HanglesInitedMatrices) {
  S21Matrix A(3, 3);
  /*   Initialize   */
  A(0, 0) = 1, A(0, 1) = 3, A(0, 2) = 6;
  A(1, 0) = 2, A(1, 1) = 5, A(1, 2) = 8;
  A(2, 0) = 3, A(2, 1) = 9, A(2, 2) = 9;
  S21Matrix B;
  B += A;
  ASSERT_EQ(true, B.EqMatrix(A));
}

TEST(OpetatorSub, HanglesInitedMatrices) {
  S21Matrix A(3, 3);
  /*   Initialize   */
  A(0, 0) = 1, A(0, 1) = 3, A(0, 2) = 6;
  A(1, 0) = 2, A(1, 1) = 5, A(1, 2) = 8;
  A(2, 0) = 3, A(2, 1) = 9, A(2, 2) = 9;
  S21Matrix B;
  B = A;
  B -= A;
  B += A;
  ASSERT_EQ(true, B.EqMatrix(A));
}

TEST(OpetatorPlus, HanglesInitedMatrices) {
  S21Matrix A(3, 3);
  /*   Initialize   */
  A(0, 0) = 1, A(0, 1) = 3, A(0, 2) = 6;
  A(1, 0) = 2, A(1, 1) = 5, A(1, 2) = 8;
  A(2, 0) = 3, A(2, 1) = 9, A(2, 2) = 9;
  S21Matrix B;
  B = A + A;
  A.MulNumber(2);
  ASSERT_EQ(true, B.EqMatrix(A));
}

TEST(OpetatorMinus, HanglesInitedMatrices) {
  S21Matrix A(3, 3);
  S21Matrix B; /* Zero Matrix */
  S21Matrix C; /* Zero Matrix */
  /*   Initialize   */
  A(0, 0) = 1, A(0, 1) = 3, A(0, 2) = 6;
  A(1, 0) = 2, A(1, 1) = 5, A(1, 2) = 8;
  A(2, 0) = 3, A(2, 1) = 9, A(2, 2) = 9;
  B = A - A;
  ASSERT_EQ(true, B.EqMatrix(C));
}

TEST(OpetatorMulMatrices, HanglesInitedMatrices) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  /*   Initialize   */
  int k = 1;
  for (int i = 0; i < A.getRow(); i++) {
    for (int j = 0; j < A.getCol(); j++) {
      A(i, j) = k++;
    }
  }
  k = 0;
  for (int i = 0; i < B.getRow(); i++) {
    for (int j = 0; j < B.getCol(); j++) {
      B(i, j) = k;
      k += 2;
    }
  }
  A *= B;
  S21Matrix R(3, 3);
  /*   Initialize   */
  R(0, 0) = 12, R(0, 1) = 18, R(0, 2) = 24;
  R(1, 0) = 24, R(1, 1) = 38, R(1, 2) = 52;
  R(2, 0) = 36, R(2, 1) = 58, R(2, 2) = 80;
  ASSERT_EQ(true, A.EqMatrix(R));
}

TEST(OpetatorMulNum, HanglesInitedMatrices) {
  S21Matrix R(3, 3);
  /*   Initialize   */
  R(0, 0) = 12, R(0, 1) = 18, R(0, 2) = 24;
  R(1, 0) = 24, R(1, 1) = 38, R(1, 2) = 52;
  R(2, 0) = 36, R(2, 1) = 58, R(2, 2) = 80;
  S21Matrix B;
  B = R * 2;
  R *= 2;
  ASSERT_EQ(true, B.EqMatrix(R));
}

TEST(SetCol, HanglesInitedMatrices) {
  S21Matrix A;
  A(0, 0) = 1, A(0, 1) = 3, A(0, 2) = 6;
  A(1, 0) = 2, A(1, 1) = 5, A(1, 2) = 8;
  A(2, 0) = 3, A(2, 1) = 9, A(2, 2) = 9;
  A.setCol(2);

  S21Matrix B(3, 2);
  B(0, 0) = 1, B(0, 1) = 3;
  B(1, 0) = 2, B(1, 1) = 5;
  B(2, 0) = 3, B(2, 1) = 9;
  ASSERT_EQ(true, A == B);
}

TEST(SetRow, HanglesInitedMatrices) {
  S21Matrix A(2, 2);
  A(0, 0) = 1, A(0, 1) = 3;
  A(1, 0) = 2, A(1, 1) = 5;
  A.setRow(4);

  S21Matrix B(4, 2);
  B(0, 0) = 1, B(0, 1) = 3;
  B(1, 0) = 2, B(1, 1) = 5;
  B(2, 0) = 0, B(2, 1) = 0;
  B(3, 0) = 0, B(3, 1) = 0;
  ASSERT_EQ(true, A == B);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}