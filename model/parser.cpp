#include "parser.h"

Matrix<MazeCell> Parser::ExtractMazeFromFile(
    const std::string file_path) {
  file_ = std::ifstream(file_path);
  if (file_.fail()) {
    throw FileDoesNotExists();
  }
  SkipEmptyLines();
  ParseMazeSizes();
  SkipEmptyLines();
  ParseCellsFromFromFile();
  return cells_;
}

void Parser::SetDefaultBorders() {
  if (row_ == 0) {
    cells_(row_, column_).SetTop();
  }
  if (column_ == 0) {
    cells_(row_, column_).SetLeft();
  }
}

void Parser::SetBordersFromFile() {
  if (matrix_type_ == MatrixTypes::kRightBorder) {
    if (symbol_ == kBorderTrue) {
      cells_(row_, column_).SetRight();
    }
  } else {
    if (symbol_ == kBorderTrue) {
      cells_(row_, column_).SetBottom();
    }
  }
}

void Parser::ParseNewRow() {
  if (file_.peek() == kEndl) {
    if (row_ != sizes_.first - 1) {
      throw InvalidMaze();
    }
    while (file_.peek() == kEndl) {
      matrix_type_ = MatrixTypes::kBottomBorder;
      file_.get(symbol_);
      row_ = 0;
      column_ = 0;
    }
  } else {
    ++row_;
    if ((file_.peek() != EOF && row_ == sizes_.first) ||
        column_ != sizes_.second) {
      throw InvalidMaze();
    }
    column_ = 0;
  }
}

void Parser::ParseCellsFromFromFile() {
  cells_ = Matrix<MazeCell>(sizes_.first, sizes_.second);
  matrix_type_ = MatrixTypes::kRightBorder;
  std::string file_string;
  row_ = 0, column_ = 0;
  while (file_.get(symbol_)) {
    if (symbol_ == kBorderDelimiter) continue;
    if (symbol_ == kEndl) {
      ParseNewRow();
      continue;
    }
    if (!IsCorrectBorderValue(symbol_) || row_ > sizes_.first - 1 ||
        column_ > sizes_.second - 1) {
      throw InvalidMaze();
    }
    SetBordersFromFile();
    SetDefaultBorders();
    ++column_;
  }

  if ((row_ != 0 && row_ < sizes_.first - 1) ||
      matrix_type_ == MatrixTypes::kRightBorder) {
    throw InvalidMaze();
  }

  file_.close();
}

void Parser::SkipEmptyLines() {
  std::string str;
  while (file_.peek() == kEndl) {
    std::getline(file_, str);
  }
}

bool Parser::IsCorrectBorderValue(const char value) const {
  return value == kBorderTrue || value == kBorderFalse;
}

void Parser::ParseMazeSizes() {
  std::string str, number;
  std::getline(file_, str);
  std::istringstream ss(str);
  int i = 0;
  while (ss >> number) {
    if (!IsDigit(number)) {
      throw InvalidMaze();
    }
    int value = std::stoi(number);
    if (i == 0) {
      sizes_.first = value;
    } else if (i == 1) {
      sizes_.second = value;
    } else {
      throw InvalidMaze();
    }
    ++i;
  }
  if (!IsCorrectMazeSizes()) {
    throw InvalidMaze();
  }
}

bool Parser::IsCorrectMazeSizes() const {
  return IsCorrectSize(sizes_.first) && IsCorrectSize(sizes_.second);
}

bool Parser::IsCorrectSize(const int size) const {
  return size >= 3 && size <= 50;
}

bool Parser::IsDigit(const std::string str) const {
  for (char ch : str) {
    if (!std::isdigit(ch)) {
      return false;
    }
  }
  return true;
}
