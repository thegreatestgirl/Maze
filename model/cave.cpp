#include "cave.h"

// Functions
void Cave::Generate(size_type rows, size_type columns) {
  Resize(rows, columns);
  Reset();
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      if (RandomChoice()) {
        cells_(i, j).Reborn();
      }
    }
  }
  SetCellsCoordinates();
}

void Cave::Update(const size_type born_limit, const size_type death_limit) {
  cells_type tmp_cells(cells_);
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      size_type alive_neighbours_quantity = GetAliveNeighboursQuantity(i, j);

      if (cells_(i, j).IsAlive() && alive_neighbours_quantity < death_limit) {
        tmp_cells(i, j).Die();
      } else if (cells_(i, j).IsDead() &&
                 alive_neighbours_quantity > born_limit) {
        tmp_cells(i, j).Reborn();
      }
    }
  }
  cells_ = tmp_cells;
}

typename Cave::size_type Cave::GetAliveNeighboursQuantity(int cell_i,
                                                          int cell_j) {
  size_type alive_neighbours_quantity = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      if ((cell_i + i) < 0 || (cell_j + j) < 0 ||
          (cell_i + i) >= (int)cells_.GetRows() ||
          (cell_j + j) >= (int)cells_.GetColumns()) {
        ++alive_neighbours_quantity;
      } else {
        if (cells_(cell_i + i, cell_j + j).IsAlive()) {
          ++alive_neighbours_quantity;
        }
      }
    }
  }
  return alive_neighbours_quantity;
}

void Cave::LoadFromFile(const std::string file_name) {
  cells_ = parser_.ExtractCaveFromFile(file_name);
  SetCellsCoordinates();
}

// Setters
void Cave::SetInitializeChance(size_type chance) { chance_ = chance; }

void Cave::Reset() {
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      cells_(i, j).Reset();
    }
  }
}

bool Cave::RandomChoice() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 100);
  return dist6(rng) <= chance_;
}
