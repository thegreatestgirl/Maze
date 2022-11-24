#include <gtest/gtest.h>

#include "model/maze.h"
#include "model/cave.h"

TEST(maze_tests, test_1) {
  Maze maze;
  EXPECT_FALSE(maze.IsInithialized());
  EXPECT_FALSE(maze.HasSolvingPath());
  maze.Generate(50, 50);
  EXPECT_TRUE(maze.IsInithialized());
  EXPECT_FALSE(maze.HasSolvingPath());
  maze.Solve({0, 0}, {49, 49});
  EXPECT_TRUE(maze.IsInithialized());
  EXPECT_TRUE(maze.HasSolvingPath());
  maze.SaveToFile("../../datasets/test_maze.txt");
}

TEST(maze_tests, test_2) {
  Maze maze;
  maze.Generate(12, 12);
  EXPECT_THROW( maze.Solve({8, 8}, {32, 19}), InvalidCellCoordinates);
}

TEST(maze_tests, test_3) {
  Maze maze;
  maze.Generate(12, 12);
  EXPECT_THROW( maze.Solve({8, 8}, {32, 19}), InvalidCellCoordinates);
}

TEST(maze_tests, test_4) {
  Maze maze;
  EXPECT_THROW(maze.LoadFromFile("aksdgjasgdhasjd.txt"), FileDoesNotExists); 
}

TEST(maze_tests, test_5) {
  Maze maze;
  maze.LoadFromFile("../../datasets/test_maze.txt");
  auto cells = maze.GetCells();
  auto solving_path = maze.GetSolvingPath();
  EXPECT_EQ(cells.GetRows(), 50);
  EXPECT_EQ(cells.GetColumns(), 50);
}

TEST(maze_tests, test_6) {
  Maze maze;
  EXPECT_THROW(maze.LoadFromFile("../../datasets/invalid_maze.txt"), InvalidMaze); 
}

TEST(maze_tests, test_7) {
  Maze maze;
  maze.LoadFromFile("../../datasets/maze_without_solution.txt");
  EXPECT_THROW(maze.Solve({0, 0}, {3, 3}), MazeSolutionDoesNotExists); 
}

TEST(cave_tests, test_1) {
  Cave cave;
  cave.LoadFromFile("../../datasets/cave_10_10.txt");
  Cave::cells_type cells = cave.GetCells();
  EXPECT_EQ(cells.GetRows(), 10);
  EXPECT_EQ(cells.GetColumns(), 10);
}

TEST(cave_tests, test_2) {
  Cave cave;
  EXPECT_THROW(cave.LoadFromFile("../../datasets/invalid_cave.txt"), InvalidCave);
}

TEST(cave_tests, test_3) {
  Cave cave;
  EXPECT_THROW(cave.LoadFromFile("iasgdiuashdiAD"), FileDoesNotExists);
}

TEST(cave_tests, test_4) {
  Cave cave;
  cave.LoadFromFile("../../datasets/cave_20_20.txt");
  cave.Update(4, 3);
  cave.Update(4, 3);
  Cave::cells_type cells = cave.GetCells();
  EXPECT_EQ(cells.GetRows(), 20);
  EXPECT_EQ(cells.GetColumns(), 20);
}


TEST(cave_tests, test_5) {
  Cave cave;
  cave.SetInitializeChance(100);
  cave.Generate(50, 50);
  cave.Update(4, 3);
  cave.Update(4, 3);
  cave.Update(4, 3);
  cave.Update(4, 3);
  Cave::cells_type cells = cave.GetCells();
  EXPECT_EQ(cells.GetRows(), 50);
  EXPECT_EQ(cells.GetColumns(), 50);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

