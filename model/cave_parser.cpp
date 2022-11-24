#include "cave_parser.h"

Matrix<CaveCell> CaveParser::ExtractCaveFromFile(
    const std::string file_path) {
  std::ifstream file(file_path);
  const char kEndl = '\n';
  const char kBorderDelimiter = ' ';

  if (file.fail()) {
    throw FileDoesNotExists();
  }

  std::string file_string;
  int i = 0, j = 0;
  char symbol;

  while (file.peek() == kEndl) {
    std::getline(file, file_string);
  }

  std::getline(file, file_string);
  std::pair<int, int> sizes = ParseCaveSizes(file_string);

  while (file.peek() == kEndl) {
    std::getline(file, file_string);
  }

  Matrix<CaveCell> cells_(sizes.first, sizes.second);

  while (file.get(symbol)) {
    if (symbol == kBorderDelimiter) continue;

    if (symbol == kEndl) {
      if (file.peek() == kEndl) {
        if (i != sizes.first - 1) {
          throw InvalidCave();
        }

      } else {
        ++i;
        if (i == sizes.first || j != sizes.second) {
          throw InvalidCave();
        }
        j = 0;
      }
      continue;
    }
    if (symbol == '1') {
      cells_(i, j).Reborn();
    } else if (symbol != '0') {
      throw InvalidCave();
    }
    ++j;
  }

  if (i < sizes.first - 1) {
    throw InvalidCave();
  }

  file.close();

  return cells_;
}

std::pair<int, int> CaveParser::ParseCaveSizes(std::string str) {
  std::istringstream ss(str);
  std::pair<int, int> sizes;
  std::string number;
  int i = 0;
  while (ss >> number) {
    if (!IsDigit(number)) {
      throw InvalidCave();
    }
    int value = std::stoi(number);
    if (i == 0) {
      sizes.first = value;
    } else if (i == 1) {
      sizes.second = value;
    } else {
      throw InvalidCave();
    }
    ++i;
  }
  return sizes;
}

bool CaveParser::IsDigit(const std::string str) const {
  for (char ch : str) {
    if (!std::isdigit(ch)) {
      return false;
    }
  }
  return true;
}
