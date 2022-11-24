#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/model.h"

class Controller {
 private:
  Model model_;

 public:
  // Maze functions
  void GenerateMaze(const int rows, const int columns);
  void SolveMaze(const unsigned i1, const unsigned j1, const unsigned i2,
                 const unsigned j2);
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


#endif  // CONTROLLER_H_
