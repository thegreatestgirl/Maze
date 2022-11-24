#include "controller.h"

// Maze functions
void Controller::GenerateMaze(const int rows, const int columns) {
  model_.GenerateMaze(rows, columns);
}

void Controller::SolveMaze(const unsigned i1, const unsigned j1,
                           const unsigned i2, const unsigned j2) {
  model_.SolveMaze(CellMatrixCoordinates{i1, j1},
                   CellMatrixCoordinates{i2, j2});
}

void Controller::SaveMazeToFile(const std::string file_path) {
  model_.SaveMazeToFile(file_path);
}

void Controller::LoadMazeFromFile(const std::string file_path) {
  model_.LoadMazeFromFile(file_path);
}

// Cave functions
void Controller::UpdateCave(const int born_limit, const int death_limit) {
  model_.UpdateCave(born_limit, death_limit);
}

void Controller::LoadCaveFromFile(const std::string file_path) {
  model_.LoadCaveFromFile(file_path);
}

void Controller::GenerateCave(int rows, int columns) {
  model_.GenerateCave(rows, columns);
}

void Controller::SetInitializeChance(int chance) {
  model_.SetInitializeChance(chance);
}

// Getters
const Maze* Controller::GetMazeReference() {
  return model_.GetMazeReference();
}

const Cave* Controller::GetCaveReference() {
  return model_.GetCaveReference();
}
