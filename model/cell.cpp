#include "cell.h"


CellCoordinates Cell::GetCoordinates() const { return coordinates_; }

void Cell::SetCordinates(const int i, const int j, const CellSizes& sizes) {
  coordinates_.top_left.x = j * sizes.width;
  coordinates_.top_left.y = i * sizes.height;

  coordinates_.top_right.x = (j + 1) * sizes.width;
  coordinates_.top_right.y = i * sizes.height;

  coordinates_.bottom_right.x = (j + 1) * sizes.width;
  coordinates_.bottom_right.y = (i + 1) * sizes.height;

  coordinates_.bottom_left.x = j * sizes.width;
  coordinates_.bottom_left.y = (i + 1) * sizes.height;
}

void Cell::SetMatrixCoordinates(const CellMatrixCoordinates coordinates) {
  matrix_coordinates_ = coordinates;
}
