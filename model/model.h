#ifndef MODEL_H_
#define MODEL_H_

#include "cave.h"
#include "maze.h"
#include "parser.h"

class Model {
 private:
  Maze maze_;
  Cave cave_;

 public:
  // Maze functions
  void GenerateMaze(int rows, int columns);
  void SolveMaze(const CellMatrixCoordinates& start_cell,
                 const CellMatrixCoordinates& end_cell);
  void SaveMazeToFile(const std::string file_path);
  void LoadMazeFromFile(const std::string file_path);

  // Cave functions
  void UpdateCave(const int born_limit, const int death_limit);
  void LoadCaveFromFile(const std::string file_path);
  void GenerateCave(int rows, int columns);
  void SetInitializeChance(int chance);

  // Getters
  const Maze* GetMazeReference();
  const Cave* GetCaveReference();
};

#endif  // MODEL_H_
