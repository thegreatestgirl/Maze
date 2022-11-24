#ifndef MAZE_CELL_H_
#define MAZE_CELL_H_

#include "cell.h"

constexpr int kDefaultCellIndex = 0;

enum class BorderStates : int8_t {
  kDoesNotExists = 0,
  kExists,
};

struct CellBorders {
  BorderStates top;
  BorderStates right;
  BorderStates bottom;
  BorderStates left;
};

enum class MazeCellVistedStates : int8_t { kVisited = 0, kDoesNotVisited };

class MazeCell : public Cell {
 public:
  using size_type = int;
  using reference = MazeCell&;
  using const_reference = const MazeCell&;
  using rvalue = MazeCell&&;

 private:
  CellBorders borders_;
  size_type index_{kDefaultCellIndex};
  MazeCellVistedStates visited_state_{MazeCellVistedStates::kDoesNotVisited};

 public:
  // Functions
  bool HasTop() const;
  bool HasRight() const;
  bool HasBottom() const;
  bool HasLeft() const;

  void RemoveTop();
  void RemoveRight();
  void RemoveBottom();
  void RemoveLeft();

  bool IsSameIndex(const_reference other);
  bool IsDifferentIndex(const_reference other);
  void CopyIndex(const_reference other);

  void RemoveBorders();

  void MakeVisited();
  void MakeUnvisited();
  bool IsVisited();

  void Reset();

  // Setters
  void SetTop();
  void SetRight();
  void SetBottom();
  void SetLeft();
  void SetIndex(const int index);

  // Getters
  int GetIndex() const;
  CellMatrixCoordinates GetMatrixCoordinates() const;
  CellBorders GetBorders() const;
};

#endif  // MAZE_CELL_H_
