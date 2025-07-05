#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
struct Matrix {
  int H, W;
  std::vector<std::vector<T>> data;

  Matrix(int h = 0, int w = 0) : H(h), W(w), data(h, std::vector<T>(w, T(0))) {
  }
  Matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.empty() ? 0 : d[0].size()), data(d) {
  }

  std::vector<T> &operator[](int i) {
    return data[i];
  }
  const std::vector<T> &operator[](int i) const {
    return data[i];
  }

  static Matrix identity(int n) {
    Matrix res(n, n);
    for (int i = 0; i < n; ++i)
      res[i][i] = T(1);
    return res;
  }

  Matrix operator-() const {
    Matrix res(H, W);
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        res[i][j] = -data[i][j];
      }
    }
    return res;
  }

  Matrix &operator+=(const Matrix &rhs) {
    assert(H == rhs.H && W == rhs.W);
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        data[i][j] += rhs[i][j];
      }
    }
    return *this;
  }

  // 行列の減算 (A -= B)
  Matrix &operator-=(const Matrix &rhs) {
    assert(H == rhs.H && W == rhs.W);
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        data[i][j] -= rhs[i][j];
      }
    }
    return *this;
  }

  Matrix &operator*=(const Matrix &rhs) {
    assert(W == rhs.H);
    Matrix res(H, rhs.W);
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < rhs.W; ++j) {
        for (int k = 0; k < W; ++k) {
          res[i][j] += data[i][k] * rhs[k][j];
        }
      }
    }
    *this = res;
    return *this;
  }

  friend Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    return Matrix(lhs) += rhs;
  }
  friend Matrix operator-(const Matrix &lhs, const Matrix &rhs) {
    return Matrix(lhs) -= rhs;
  }
  friend Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    return Matrix(lhs) *= rhs;
  }

  Matrix pow(long long n) const {
    assert(H == W);
    Matrix res = Matrix::identity(H);
    Matrix x = *this;
    while (n > 0) {
      if (n & 1)
        res *= x;
      x *= x;
      n >>= 1;
    }
    return res;
  }

  // ストリーム出力 (cout << A)
  friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &mat) {
    for (int i = 0; i < mat.H; ++i) {
      for (int j = 0; j < mat.W; ++j) {
        os << mat[i][j] << (j == mat.W - 1 ? "" : " ");
      }
      if (i != mat.H - 1)
        os << "\n";
    }
    return os;
  }
};