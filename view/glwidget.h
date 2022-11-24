#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>

#include <QGLWidget>

#include "../model/maze.h"

// class GLWidget : public QOpenGLWidget
class GLWidget : public QGLWidget {
  Q_OBJECT
 public:
  explicit GLWidget(QWidget* parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

 private:
  const Maze* maze_;

 private:
  void DrawMaze();
  void DrawCell(const MazeCell& cell);
  void DrawTopBorder(const CellCoordinates& coordinates);
  void DrawRightBorder(const CellCoordinates& coordinates);
  void DrawBottomBorder(const CellCoordinates& coordinates);
  void DrawLeftBorder(const CellCoordinates& coordinates);
  void DrawSolvingPath();
  void DrawSolvingPathPoints(const Maze::solving_path_type& solving_path);

 public:
  void SetMaze(const Maze* maze);
};

#endif  // GLWIDGET_H
