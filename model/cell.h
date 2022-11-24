#ifndef CELL_H_
#define CELL_H_

#include <iostream>

struct CellSizes {
  unsigned int width;
  unsigned int height;
};

struct CellMatrixCoordinates {
  unsigned int i;
  unsigned int j;
};

struct Coordinates2D {
  double x;
  double y;
};

struct CellCoordinates {
  Coordinates2D top_left;
  Coordinates2D top_right;
  Coordinates2D bottom_right;
  Coordinates2D bottom_left;
};

class Cell {
 protected:
  CellMatrixCoordinates matrix_coordinates_;
  CellCoordinates coordinates_;

 public:
  void SetMatrixCoordinates(const CellMatrixCoordinates coordinates);
  void SetCordinates(const int i, const int j, const CellSizes& sizes);
  CellCoordinates GetCoordinates() const;

  virtual void Reset() = 0;
};


#endif  // CELL_H_
