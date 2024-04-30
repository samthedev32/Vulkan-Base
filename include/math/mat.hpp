#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <vector>

#include "vec.hpp"

// Radian-Degree Conversion Functions
#define rads(d) (d * M_PI / 180.0f)
#define degs(r) (r * 180.0f / M_PI)

// MIN & MAX
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a < b ? b : a)

// Variable Dimension Matrix
template <uint8_t R, uint8_t C = R, typename T = float> struct mat {
  static_assert(R != 0 && C != 0, "Null-Matrices are not supported");

  T data[R][C];

  // Constructors & Destructor

  mat(T v = 0);
  mat(std::vector<std::vector<T>> m);
  template <uint8_t inR, uint8_t inC, typename inT> mat(mat<inR, inC, inT> m);

  ~mat();

  // Arithmetic Operators

  mat<R, C, T> operator+(mat<R, C, T> m) const;
  mat<R, C, T> operator-(mat<R, C, T> m) const;
  // matrix division is not defined
  template <uint8_t inR, uint8_t inC, typename inT>
  mat<MAX(R, inR), MAX(C, inC)> operator*(mat<inR, inC, inT> m) const;

  template <uint8_t inD, typename inT>
  vec<inD, inT> operator*(vec<inD, inT> v) const;

  // Assignment Operators

  template <uint8_t inR, uint8_t inC, typename inT>
  void operator=(mat<inR, inC, inT> m);
  template <uint8_t inR, uint8_t inC, typename inT>
  void operator*=(mat<inR, inC, inT> m);

  // Relational Operators

  template <uint8_t inR, uint8_t inC, typename inT>
  bool operator==(mat<inR, inC, inT> m) const;
  template <uint8_t inR, uint8_t inC, typename inT>
  bool operator!=(mat<inR, inC, inT> m) const;

  // Other Operators

  T operator()(uint8_t row, uint8_t col) const;
  T &operator()(uint8_t row, uint8_t col);

  // Functions (Instance Methods)

  bool isSquare() const;
  void inverse();

  // Functions (Static)

  static mat<R> identity();

  static mat<4> rotationX(float rad);
  static mat<4> rotationY(float rad);
  static mat<4> rotationZ(float rad);
  static mat<4> rotation(vec<3> rad);

  static mat<4> translation(vec<3> v);
  static mat<4> scale(vec<3> v);

  // Functions (Dimension-Specific)

  static mat<4> perspective(float fovrads, float aspect, float near, float far);

  static mat<4> ortho(float left, float right, float bottom, float top,
                      float fnear, float ffar);

  static mat<4> lookat(vec<3> pos, vec<3> target,
                       vec<3> up = {0.0f, 1.0f, 0.0f});
};

// Constructors & Destructor

template <uint8_t R, uint8_t C, typename T> mat<R, C, T>::mat(T v) {
  for (int r = 0; r < R; r++)
    for (int c = 0; c < C; c++)
      this->data[r][c] = v;
}

template <uint8_t R, uint8_t C, typename T>
mat<R, C, T>::mat(std::vector<std::vector<T>> m) {
  for (uint8_t r = 0; r < R; r++)
    for (uint8_t c = 0; c < C; c++)
      this->data[r][c] = r < m.size() && c < m[r].size() ? m[r][c] : 0;
}

template <uint8_t R, uint8_t C, typename T>
template <uint8_t inR, uint8_t inC, typename inT>
mat<R, C, T>::mat(mat<inR, inC, inT> m) {
  *this = m;
}

template <uint8_t R, uint8_t C, typename T> mat<R, C, T>::~mat() {}

// Arithmetic Operators

template <uint8_t R, uint8_t C, typename T>
mat<R, C, T> mat<R, C, T>::operator+(mat<R, C, T> m) const {
  mat<R, C, T> out;

  for (uint8_t r = 0; r < R; r++)
    for (uint8_t c = 0; c < C; c++)
      out.data[r][c] = this->data[r][c] + m.data[r][c];

  return out;
}

template <uint8_t R, uint8_t C, typename T>
mat<R, C, T> mat<R, C, T>::operator-(mat<R, C, T> m) const {
  mat<R, C, T> out;

  for (uint8_t r = 0; r < R; r++)
    for (uint8_t c = 0; c < C; c++)
      out.data[r][c] = this->data[r][c] - m.data[r][c];

  return out;
}

template <uint8_t R, uint8_t C, typename T>
template <uint8_t inR, uint8_t inC, typename inT>
mat<MAX(R, inR), MAX(C, inC)>
mat<R, C, T>::operator*(mat<inR, inC, inT> m) const {
  mat<MAX(R, inR), MAX(C, inC)> out;

  if (C != inR)
    return out;

  for (uint8_t r = 0; r < MAX(R, inR); r++)
    for (uint8_t c = 0; c < MAX(C, inC); c++)
      for (uint8_t k = 0; k < C; k++)
        out.data[r][c] += this->data[r][k] * m.data[k][c];

  return out;
}

template <uint8_t R, uint8_t C, typename T>
template <uint8_t inD, typename inT>
vec<inD, inT> mat<R, C, T>::operator*(vec<inD, inT> v) const {
  vec<inD, inT> out;

  // TODO

  return out;
}

// Assignment Operators

template <uint8_t R, uint8_t C, typename T>
template <uint8_t inR, uint8_t inC, typename inT>
void mat<R, C, T>::operator=(mat<inR, inC, inT> m) {
  for (int r = 0; r < R; r++)
    for (int c = 0; c < C; c++)
      this->data[r][c] = r < inR && c < inC ? m.data[r][c] : 0;
}

template <uint8_t R, uint8_t C, typename T>
template <uint8_t inR, uint8_t inC, typename inT>
void mat<R, C, T>::operator*=(mat<inR, inC, inT> m) {
  *this = *this * m;
}

// Relational Operators

template <uint8_t R, uint8_t C, typename T>
template <uint8_t inR, uint8_t inC, typename inT>
bool mat<R, C, T>::operator==(mat<inR, inC, inT> m) const {
  for (int r = 0; r < std::min(R, inR); r++)
    for (int c = 0; c < std::min(C, inC); c++)
      if (this->data[r][c] != m.data[r][c])
        return false;
  return true;
}

template <uint8_t R, uint8_t C, typename T>
template <uint8_t inR, uint8_t inC, typename inT>
bool mat<R, C, T>::operator!=(mat<inR, inC, inT> m) const {
  for (int r = 0; r < std::min(R, inR); r++)
    for (int c = 0; c < std::min(C, inC); c++)
      if (this->data[r][c] == m.data[r][c])
        return false;
  return true;
}

// Other Operators

template <uint8_t R, uint8_t C, typename T>
T mat<R, C, T>::operator()(uint8_t row, uint8_t col) const {
  return this->data[row % R][col % C];
}

template <uint8_t R, uint8_t C, typename T>
T &mat<R, C, T>::operator()(uint8_t row, uint8_t col) {
  return this->data[row % R][col % C];
}

// Functions (Instance Methods)

template <uint8_t R, uint8_t C, typename T>
bool mat<R, C, T>::isSquare() const {
  return R == C;
}

void inverse();

// T sum();

// Functions (Static)

template <uint8_t R, uint8_t C, typename T> mat<R, R> mat<R, C, T>::identity() {
  mat<R> out;

  for (uint8_t rc = 0; rc < MIN(R, C); rc++)
    out.data[rc][rc] = 1;

  return out;
}

template <uint8_t R, uint8_t C, typename T>
mat<4> mat<R, C, T>::rotationX(float rad) {
  mat<4> matrix;
  matrix(0, 0) = 1.0f;
  matrix(1, 1) = cosf(rad);
  matrix(1, 2) = sinf(rad);
  matrix(2, 1) = -sinf(rad);
  matrix(2, 2) = cosf(rad);
  matrix(3, 3) = 1.0f;
  return matrix;
}

template <uint8_t R, uint8_t C, typename T>
mat<4> mat<R, C, T>::rotationY(float rad) {
  mat<4> matrix;
  matrix(0, 0) = cosf(rad);
  matrix(0, 2) = sinf(rad);
  matrix(2, 0) = -sinf(rad);
  matrix(1, 1) = 1.0f;
  matrix(2, 2) = cosf(rad);
  matrix(3, 3) = 1.0f;
  return matrix;
}

template <uint8_t R, uint8_t C, typename T>
mat<4> mat<R, C, T>::rotationZ(float rad) {
  mat<4> matrix;
  matrix(0, 0) = cosf(rad);
  matrix(0, 1) = sinf(rad);
  matrix(1, 0) = -sinf(rad);
  matrix(1, 1) = cosf(rad);
  matrix(2, 2) = 1.0f;
  matrix(3, 3) = 1.0f;
  return matrix;
}

template <uint8_t R, uint8_t C, typename T>
mat<4> mat<R, C, T>::rotation(vec<3> rad) {
  mat<4> matrix, x, y, z;

  x = rotationX(rad->x);
  y = rotationY(rad->y);
  z = rotationZ(rad->z);

  matrix = identity();
  matrix = x * y;
  matrix = matrix * z;

  return matrix;
}

template <uint8_t R, uint8_t C, typename T> mat<4> translation(vec<3> v) {
  mat<4> out = mat<4>::identity();

  out.data[3][0] = v->x;
  out.data[3][1] = v->y;
  out.data[3][2] = v->z;

  return out;
}

template <uint8_t R, uint8_t C, typename T> mat<4> scale(vec<3> v) {
  mat<4> out;

  out.data[0][0] = v->x;
  out.data[1][1] = v->y;
  out.data[2][2] = v->z;
  out.data[3][3] = 1.0f;

  return out;
}

// Functions (Dimension-Specific)

template <uint8_t R, uint8_t C, typename T>
mat<4> mat<R, C, T>::perspective(float fovrads, float aspect, float near,
                                 float far) {
  float tanHalfFov = tan(fovrads / 2.0f);

  mat<4> out;
  out.data[0][0] = 1.0f / (aspect * tanHalfFov);
  out.data[1][1] = 1.0f / (tanHalfFov);
  out.data[2][2] = -(far + near) / (far - near);
  out.data[2][3] = -1.0f;
  out.data[3][2] = -(2.0f * far * near) / (far - near);
  return out;
}

template <uint8_t R, uint8_t C, typename T>
mat<4> mat<R, C, T>::ortho(float left, float right, float bottom, float top,
                           float near, float far) {
  mat<4> out = identity();
  out.data[0][0] = 2.0f / (right - left);
  out.data[1][1] = 2.0f / (top - bottom);
  out.data[2][2] = -2.0f / (far - near);
  out.data[3][0] = -(right + left) / (right - left);
  out.data[3][1] = -(top + bottom) / (top - bottom);
  out.data[3][2] = -(far + near) / (far - near);
  return out;
}

template <uint8_t R, uint8_t C, typename T>
mat<4> mat<R, C, T>::lookat(vec<3> pos, vec<3> target, vec<3> up) {
  vec<3> f = (target - pos).normalize();
  vec<3> s = vec<3>::cross(f, up).normalize();
  vec<3> u = vec<3>::cross(s, f);

  mat<4> out = identity();
  out.data[0][0] = s[0];
  out.data[1][0] = s[1];
  out.data[2][0] = s[2];
  out.data[0][1] = u[0];
  out.data[1][1] = u[1];
  out.data[2][1] = u[2];
  out.data[0][2] = -f[0];
  out.data[1][2] = -f[1];
  out.data[2][2] = -f[2];
  out.data[3][0] = -vec<3>::dot(s, pos);
  out.data[3][1] = -vec<3>::dot(u, pos);
  out.data[3][2] = vec<3>::dot(f, pos);
  return out;
}