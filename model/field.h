#ifndef FIELD_H_
#define FIELD_H_

#include <iostream>
#include <random>

#include "cell.h"

constexpr int kMaxFieldSizePX = 500;

template <class T>
class Field {
 public:
  using size_type = unsigned int;
  using cells_type = T;

 protected:
  cells_type cells_;
  CellSizes cell_sizes_;

 public:
  // Functions
  virtual void Generate(size_type rows, size_type columns) = 0;
  virtual void LoadFromFile(const std::string file_name) = 0;
  virtual void Reset() = 0;
  virtual bool RandomChoice() = 0;

  void Resize(size_type rows, size_type columns);
  CellSizes CalculateCellSizes();
  void SetCellsCoordinates();

  // Getters
  const cells_type& GetCells() const;
};

template <typename T>
void Field<T>::Resize(size_type rows, size_type columns) {
  cells_.Resize(rows, columns);
}

template <typename T>
CellSizes Field<T>::CalculateCellSizes() {
  return CellSizes{kMaxFieldSizePX / cells_.GetColumns(),
                   kMaxFieldSizePX / cells_.GetRows()};
}

template <typename T>
void Field<T>::SetCellsCoordinates() {
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      cells_(i, j).SetMatrixCoordinates(CellMatrixCoordinates{i, j});
      cells_(i, j).SetCordinates(i, j, CalculateCellSizes());
    }
  }
}

template <typename T>
const typename Field<T>::cells_type& Field<T>::GetCells() const {
  return cells_;
}

#endif  // FIELD_H_
