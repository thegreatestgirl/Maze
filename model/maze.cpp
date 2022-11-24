#include "maze.h"


void Maze::GenerateFirstRow() {
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    cells_(current_row_, j).SetTop();
    if (j == 0) {
      cells_(current_row_, j).SetLeft();
    } else if (j == cells_.GetColumns() - 1) {
      cells_(current_row_, j).SetRight();
    }
  }
  NumerateRow();
  CreateRightBorders();
  CreateBottomBorders();
}

void Maze::NumerateRow() {
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    if (cells_(current_row_, j).GetIndex() == kDefaultCellIndex) {
      cells_(current_row_, j).SetIndex(set_number_);
      ++set_number_;
    }
  }
}

void Maze::CreateRightBorders() {
  for (size_type j = 0; j < cells_.GetColumns() - 1; ++j) {
    if (RandomChoice() ||
        cells_(current_row_, j).IsSameIndex(cells_(current_row_, j + 1))) {
      cells_(current_row_, j).SetRight();
    } else {
      MergeCells(j);
    }
  }
}

void Maze::MergeCells(const size_type start_cell_index) {
  size_type current_index = cells_(current_row_, start_cell_index).GetIndex();
  size_type next_index = cells_(current_row_, start_cell_index + 1).GetIndex();
  for (size_type i = 0; i < cells_.GetColumns(); ++i) {
    if (cells_(current_row_, i).GetIndex() == static_cast<int>(next_index)) {
      cells_(current_row_, i).SetIndex(current_index);
    }
  }
}

void Maze::CreateBottomBorders() {
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    if (RandomChoice()) {
      if (j == 0) {
        if (cells_(current_row_, j)
                .IsDifferentIndex(cells_(current_row_, j + 1))) {
          continue;
        }
      } else if (j == cells_.GetColumns() - 1) {
        if (cells_(current_row_, j)
                .IsDifferentIndex(cells_(current_row_, j - 1))) {
          continue;
        }
      } else {
        if (cells_(current_row_, j)
                .IsDifferentIndex(cells_(current_row_, j - 1)) &&
            cells_(current_row_, j)
                .IsDifferentIndex(cells_(current_row_, j + 1))) {
          continue;
        }
      }
      cells_(current_row_, j).SetBottom();
    }
  }
  ValidateBottomBorders();
}

void Maze::ValidateBottomBorders() {
  size_type start = 0, end = 0, bottoms_quantiy = 0;
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    if (cells_(current_row_, j).IsSameIndex(cells_(current_row_, j + 1))) {
      if (cells_(current_row_, j).HasBottom()) {
        ++bottoms_quantiy;
      }
      ++end;
    } else {
      if (cells_(current_row_, j).HasBottom()) {
        ++bottoms_quantiy;
      }
      if (end - start + 1 == bottoms_quantiy) {
        cells_(current_row_, start).RemoveBottom();
      }
      bottoms_quantiy = 0;
      start = j + 1;
      end = start;
    }
  }
}

void Maze::PrepareNewRow() {
  CopyPrewiousRowWithoutTopBordes();
  RemoveAllRightBorders();
  DenumerateCellsWithBottomBorder();
  RemoveAllBottomBorders();
}

void Maze::CopyPrewiousRowWithoutTopBordes() {
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    cells_(current_row_, j) = cells_(current_row_ - 1, j);
    cells_(current_row_, j).RemoveTop();
  }
}

void Maze::RemoveAllRightBorders() {
  for (size_type j = 0; j < cells_.GetColumns() - 1; ++j) {
    cells_(current_row_, j).RemoveRight();
  }
}

void Maze::DenumerateCellsWithBottomBorder() {
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    if (cells_(current_row_, j).HasBottom()) {
      cells_(current_row_, j).SetIndex(kDefaultCellIndex);
    }
  }
}

void Maze::RemoveAllBottomBorders() {
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    cells_(current_row_, j).RemoveBottom();
  }
}

void Maze::GenerateLastRow() {
  ++current_row_;
  PrepareNewRow();
  NumerateRow();
  CreateRightBorders();
  for (size_type j = 0; j < cells_.GetColumns(); ++j) {
    cells_(current_row_, j).SetBottom();
  }
  for (size_type j = 0; j < cells_.GetColumns() - 1; ++j) {
    if (cells_(current_row_, j).IsDifferentIndex(cells_(current_row_, j + 1))) {
      cells_(current_row_, j).RemoveRight();
      MergeCells(j);
    }
  }
}

void Maze::GenerateMiddleRows() {
  for (size_type row = 1; row < cells_.GetRows() - 1; ++row) {
    ++current_row_;
    PrepareNewRow();
    NumerateRow();
    CreateRightBorders();
    CreateBottomBorders();
  }
}

// Functions
void Maze::Generate(size_type rows, size_type columns) {
  Resize(rows, columns);
  Reset();
  GenerateFirstRow();
  GenerateMiddleRows();
  GenerateLastRow();
  SetCellsCoordinates();
}

void Maze::Reset() {
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      cells_(i, j).Reset();
    }
  }
  set_number_ = kDefaultSetNumber;
  current_row_ = kDefaultRow;
  solving_path_.clear();
  cell_sizes_ = CalculateCellSizes();
}

// Getters
const typename Maze::solving_path_type& Maze::GetSolvingPath() const {
  return solving_path_;
}

bool Maze::RandomChoice() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);
  return dist6(rng);
}

void Maze::SaveToFile(const std::string file_path) {
  std::ofstream maze_file(file_path);
  maze_file << cells_.GetRows() << " " << cells_.GetColumns() << std::endl;
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      if (cells_(i, j).HasRight()) {
        maze_file << kBorderTrue << kBorderDelimiter;
      } else {
        maze_file << kBorderFalse << kBorderDelimiter;
      }
    }
    maze_file << std::endl;
  }
  maze_file << std::endl;
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      if (cells_(i, j).HasBottom()) {
        maze_file << kBorderTrue << kBorderDelimiter;
      } else {
        maze_file << kBorderFalse << kBorderDelimiter;
      }
    }
    maze_file << std::endl;
  }
  maze_file.close();
}

bool Maze::IsCorrectCellMatrixCoordinates(
    const CellMatrixCoordinates& start_cell,
    const CellMatrixCoordinates& end_cell) {
  return start_cell.i <= cells_.GetRows() - 1 &&
         end_cell.i <= cells_.GetRows() - 1 &&
         start_cell.j <= cells_.GetColumns() - 1 &&
         end_cell.j <= cells_.GetColumns() - 1 &&
         (start_cell.i != end_cell.i && start_cell.j != end_cell.j);
}

void Maze::PrepareMazeForSolving() {
  solving_path_.clear();
  for (size_type i = 0; i < cells_.GetRows(); ++i) {
    for (size_type j = 0; j < cells_.GetColumns(); ++j) {
      cells_(i, j).MakeUnvisited();
    }
  }
}

void Maze::Solve(const CellMatrixCoordinates& start_cell,
                 const CellMatrixCoordinates& end_cell) {
  if (!IsCorrectCellMatrixCoordinates(start_cell, end_cell)) {
    throw InvalidCellCoordinates();
  }
  PrepareMazeForSolving();

  cells_(start_cell.i, start_cell.j).MakeVisited();
  solving_stack_.push(cells_(start_cell.i, start_cell.j));

  while (true) {
    MazeCell current_cell = solving_stack_.top();
    CellMatrixCoordinates current_cell_coordinates =
        current_cell.GetMatrixCoordinates();

    size_type current_cell_i = current_cell_coordinates.i,
              current_cell_j = current_cell_coordinates.j;

    if (current_cell_i == end_cell.i && current_cell_j == end_cell.j) {
      break;
    }

    if (current_cell_i > 0 &&
        !cells_(current_cell_i - 1, current_cell_j).HasBottom()) {
      if (!cells_(current_cell_i - 1, current_cell_j).IsVisited()) {
        solving_stack_.push(cells_(current_cell_i - 1, current_cell_j));
        cells_(current_cell_i - 1, current_cell_j).MakeVisited();
        continue;
      }
    }
    if (!current_cell.HasRight()) {
      if (!cells_(current_cell_i, current_cell_j + 1).IsVisited()) {
        solving_stack_.push(cells_(current_cell_i, current_cell_j + 1));
        cells_(current_cell_i, current_cell_j + 1).MakeVisited();
        continue;
      }
    }
    if (!current_cell.HasBottom()) {
      if (!cells_(current_cell_i + 1, current_cell_j).IsVisited()) {
        solving_stack_.push(cells_(current_cell_i + 1, current_cell_j));
        cells_(current_cell_i + 1, current_cell_j).MakeVisited();
        continue;
      }
    }
    if (current_cell_j > 0 &&
        !cells_(current_cell_i, current_cell_j - 1).HasRight()) {
      if (!cells_(current_cell_i, current_cell_j - 1).IsVisited()) {
        solving_stack_.push(cells_(current_cell_i, current_cell_j - 1));
        cells_(current_cell_i, current_cell_j - 1).MakeVisited();
        continue;
      }
    }

    solving_stack_.pop();
    if (solving_stack_.empty()) {
      throw MazeSolutionDoesNotExists();
    }
  }

  CreateSolvingPath();
}

void Maze::CreateSolvingPath() {
  while (!solving_stack_.empty()) {
    MazeCell top_cell = solving_stack_.top();
    CellCoordinates cell_coordinates = top_cell.GetCoordinates();
    double center_x = static_cast<double>(cell_coordinates.bottom_left.x +
                                          cell_coordinates.bottom_right.x) /
                      2.0,
           center_y = static_cast<double>(cell_coordinates.top_left.y +
                                          cell_coordinates.bottom_left.y) /
                      2.0;
    solving_stack_.pop();
    solving_path_.push_back(Coordinates2D{center_x, center_y});
  }
}

bool Maze::IsInithialized() const {
  return cells_.GetRows() != kDefaultRows;
}

bool Maze::HasSolvingPath() const { return !solving_path_.empty(); }

void Maze::LoadFromFile(const std::string file_path) {
  cells_ = parser_.ExtractMazeFromFile(file_path);
  cell_sizes_ = CalculateCellSizes();
  SetCellsCoordinates();
  solving_path_.clear();
}
