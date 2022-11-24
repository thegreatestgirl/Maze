#ifndef PARSER_H_
#define PARSER_H_

#include <fstream>
#include <sstream>

#include "exceptions.h"
#include "matrix.h"
#include "maze_cell.h"

const char kEndl = '\n';
const char kBorderTrue = '1';
const char kBorderFalse = '0';
const char kBorderDelimiter = ' ';

enum class MatrixTypes : int8_t { kRightBorder = 0, kBottomBorder };

class Parser {
 private:
  std::ifstream file_;
  std::pair<int, int> sizes_;
  int row_, column_;
  char symbol_;
  Matrix<MazeCell> cells_;
  MatrixTypes matrix_type_;

 public:
  Matrix<MazeCell> ExtractMazeFromFile(const std::string file_path);

 private:
  void ParseMazeSizes();
  void ParseCellsFromFromFile();
  bool IsCorrectMazeSizes() const;
  bool IsCorrectSize(const int size) const;
  bool IsDigit(const std::string str) const;
  bool IsCorrectBorderValue(const char value) const;
  void SkipEmptyLines();

  void SetDefaultBorders();
  void SetBordersFromFile();
  void ParseNewRow();
};

#endif  // PARSER_H_
