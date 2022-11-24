#include "maze_cell.h"

// Functions
bool MazeCell::HasTop() const { return borders_.top == BorderStates::kExists; }

bool MazeCell::HasRight() const {
  return borders_.right == BorderStates::kExists;
}

bool MazeCell::HasBottom() const {
  return borders_.bottom == BorderStates::kExists;
}

bool MazeCell::HasLeft() const {
  return borders_.left == BorderStates::kExists;
}

void MazeCell::RemoveTop() { borders_.top = BorderStates::kDoesNotExists; }

void MazeCell::RemoveRight() { borders_.right = BorderStates::kDoesNotExists; }

void MazeCell::RemoveBottom() {
  borders_.bottom = BorderStates::kDoesNotExists;
}

void MazeCell::RemoveLeft() { borders_.left = BorderStates::kDoesNotExists; }

bool MazeCell::IsSameIndex(const_reference other) {
  return index_ == other.index_;
}

bool MazeCell::IsDifferentIndex(const_reference other) {
  return index_ != other.index_;
}

void MazeCell::CopyIndex(const_reference other) { index_ = other.index_; }

void MazeCell::RemoveBorders() {
  RemoveTop();
  RemoveRight();
  RemoveBottom();
  RemoveLeft();
}

void MazeCell::MakeVisited() {
  visited_state_ = MazeCellVistedStates::kVisited;
}

void MazeCell::MakeUnvisited() {
  visited_state_ = MazeCellVistedStates::kDoesNotVisited;
}

bool MazeCell::IsVisited() {
  return visited_state_ == MazeCellVistedStates::kVisited;
}

void MazeCell::Reset() {
  RemoveBorders();
  SetIndex(kDefaultCellIndex);
  MakeUnvisited();
}

// Setters
void MazeCell::SetTop() { borders_.top = BorderStates::kExists; }

void MazeCell::SetRight() { borders_.right = BorderStates::kExists; }

void MazeCell::SetBottom() { borders_.bottom = BorderStates::kExists; }

void MazeCell::SetLeft() { borders_.left = BorderStates::kExists; }

void MazeCell::SetIndex(const int index) { index_ = index; }

// Getters
typename MazeCell::size_type MazeCell::GetIndex() const { return index_; }

CellMatrixCoordinates MazeCell::GetMatrixCoordinates() const {
  return matrix_coordinates_;
}

CellBorders MazeCell::GetBorders() const { return borders_; }
