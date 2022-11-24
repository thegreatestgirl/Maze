#ifndef CAVE_H_
#define CAVE_H_

#include "cave_cell.h"
#include "cave_parser.h"
#include "field.h"
#include "matrix.h"

class Cave : public Field<Matrix<CaveCell>> {
 public:
  using size_type = Matrix<CaveCell>::size_type;
  using cells_type = Matrix<CaveCell>;

 private:
  CaveParser parser_;
  size_type chance_;

 public:
  // Functions
  void Generate(size_type rows, size_type columns);
  void Update(const size_type born_limit, const size_type death_limit);
  void LoadFromFile(const std::string file_name);

  // Setters
  void SetInitializeChance(size_type chance);

 private:
  size_type GetAliveNeighboursQuantity(int cell_i, int cell_j);
  void Reset();
  bool RandomChoice();
};


#endif  // CAVE_H_
