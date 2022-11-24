#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>
#include <iostream>

#include "exceptions.h"

constexpr unsigned int kDefaultRows = 1;
constexpr unsigned int kDefaultColumns = 1;

template <class T>
class Matrix {
 public:
  using size_type = unsigned int;
  using value_type = T;
  using reference = Matrix&;
  using const_reference = const Matrix&;
  using rvalue = Matrix&&;
  using self_type = Matrix;

 private:
  size_type rows_, columns_;
  value_type** values_;

 public:
  // Constructors
  Matrix();
  Matrix(size_type rows, size_type columns);
  Matrix(const_reference other);
  Matrix(rvalue other);
  ~Matrix();
  reference operator=(const_reference other);
  reference operator=(rvalue other);

  // Functions
  void Resize(const size_type rows, const size_type columns);

  // Getters
  size_type GetRows() const;
  size_type GetColumns() const;

  // Overloads
  value_type& operator()(const size_type i, const size_type j);

 private:
  void AllocateValues();
  void DeleteValues();
  void Copy(const_reference other);
  void CopyMatrixValues(const_reference src);
};

template <typename T>
Matrix<T>::Matrix() : rows_(kDefaultRows), columns_(kDefaultColumns) {
  AllocateValues();
}

template <typename T>
Matrix<T>::Matrix(size_type rows, size_type columns)
    : rows_(rows), columns_(columns) {
  AllocateValues();
}

template <typename T>
Matrix<T>::Matrix(const_reference other) {
  *this = other;
}

template <typename T>
Matrix<T>::Matrix(rvalue other) {
  *this = std::move(other);
}

template <typename T>
Matrix<T>::~Matrix() {
  DeleteValues();
}

template <typename T>
typename Matrix<T>::reference Matrix<T>::operator=(const_reference other) {
  if (this != &other) {
    Copy(other);
  }
  return *this;
}

template <typename T>
typename Matrix<T>::reference Matrix<T>::operator=(rvalue other) {
  if (this != &other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    values_ = other.values_;
    other.rows_ = kDefaultRows;
    other.columns_ = kDefaultColumns;
    other.values_ = nullptr;
  }
  return *this;
}

template <typename T>
void Matrix<T>::AllocateValues() {
  if (rows_ == 0 || columns_ == 0) {
    throw InvalidMatrixSizes();
  }
  values_ = new value_type*[rows_];
  for (size_type i = 0; i < rows_; i++) {
    values_[i] = new value_type[columns_]{};
  }
}

template <typename T>
void Matrix<T>::DeleteValues() {
  if (values_) {
    for (size_type i = 0; i < rows_; ++i) {
      delete[] values_[i];
    }
    delete[] values_;
  }
}

template <typename T>
void Matrix<T>::Copy(const_reference other) {
  rows_ = other.rows_;
  columns_ = other.columns_;
  AllocateValues();
  CopyMatrixValues(other);
}

template <typename T>
void Matrix<T>::CopyMatrixValues(const_reference src) {
  for (size_type n = 0; n < rows_ * columns_; n++) {
    size_type i = n / columns_, j = n % columns_;
    values_[i][j] = src.values_[i][j];
  }
}

template <typename T>
T& Matrix<T>::operator()(const size_type i, const size_type j) {
  return values_[i][j];
}

template <typename T>
typename Matrix<T>::size_type Matrix<T>::GetRows() const {
  return rows_;
}

template <typename T>
typename Matrix<T>::size_type Matrix<T>::GetColumns() const {
  return columns_;
}

template <typename T>
void Matrix<T>::Resize(const size_type rows, const size_type columns) {
  DeleteValues();
  rows_ = rows;
  columns_ = columns;
  AllocateValues();
}

#endif  // SRC_MATRIX_H_
