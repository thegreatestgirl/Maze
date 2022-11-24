#ifndef CAVE_PARSER_H_
#define CAVE_PARSER_H_

#include <fstream>
#include <sstream>

#include "cave_cell.h"
#include "exceptions.h"
#include "matrix.h"

class CaveParser {
 public:
  Matrix<CaveCell> ExtractCaveFromFile(const std::string file_path);

 private:
  std::pair<int, int> ParseCaveSizes(std::string str);
  bool IsDigit(const std::string str) const;
};

#endif  // CAVE_PARSER_H_
