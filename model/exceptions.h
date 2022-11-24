#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

class InvalidMaze : public std::exception {
 public:
  const char *what() const throw() { return "Invalid maze"; }
};

class FileDoesNotExists : public std::exception {
 public:
  const char *what() const throw() { return "File does not exists"; }
};

class InvalidCellCoordinates : public std::exception {
 public:
  const char *what() const throw() { return "Invalid cell coordinates"; }
};

class MazeSolutionDoesNotExists : public std::exception {
 public:
  const char *what() const throw() { return "Maze solution does not exists"; }
};

class InvalidMatrixSizes : public std::exception {
 public:
  const char *what() const throw() { return "Invalid matrix sizes"; }
};

class InvalidCave : public std::exception {
 public:
  const char *what() const throw() { return "Invalid cave"; }
};


#endif  // EXCEPTIONS_H_
