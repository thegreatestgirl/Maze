#include "model.h"

// Maze functions
void Model::GenerateMaze(int rows, int columns) {
  maze_.Generate(rows, columns);
}

void Model::SolveMaze(const CellMatrixCoordinates& start_cell,
                      const CellMatrixCoordinates& end_cell) {
  maze_.Solve(start_cell, end_cell);
}

void Model::SaveMazeToFile(const std::string file_path) {
  maze_.SaveToFile(file_path);
}

void Model::LoadMazeFromFile(const std::string file_path) {
  maze_.LoadFromFile(file_path);
}

// Cave functions
void Model::UpdateCave(const int born_limit, const int death_limit) {
  cave_.Update(born_limit, death_limit);
}

void Model::LoadCaveFromFile(const std::string file_path) {
  cave_.LoadFromFile(file_path);
}

void Model::GenerateCave(int rows, int columns) {
  cave_.Generate(rows, columns);
}

void Model::SetInitializeChance(int chance) {
  cave_.SetInitializeChance(chance);
}

// Getters
const Maze* Model::GetMazeReference() { return &maze_; }

const Cave* Model::GetCaveReference() { return &cave_; }
