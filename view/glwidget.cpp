#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent) {}

void GLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-4, 504, 504, -4);
  if (maze_->IsInithialized()) {
    DrawMaze();
    if (maze_->HasSolvingPath()) {
      DrawSolvingPath();
    }
  }
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0, (float)w / h, 0.01, 100.0);
  updateGL();
  // update();
}

void GLWidget::DrawMaze() {
  Matrix<MazeCell> cells = maze_->GetCells();
  glLineWidth(2);
  glBegin(GL_LINES);
  glColor3f(1, 1, 1);
  for (Matrix<MazeCell>::size_type i = 0; i < cells.GetRows(); ++i) {
    for (Matrix<MazeCell>::size_type j = 0; j < cells.GetColumns(); ++j) {
      DrawCell(cells(i, j));
    }
  }
  glEnd();
}

void GLWidget::DrawCell(const MazeCell& cell) {
  CellCoordinates coordinates = cell.GetCoordinates();
  if (cell.HasTop()) {
    DrawTopBorder(coordinates);
  }
  if (cell.HasRight()) {
    DrawRightBorder(coordinates);
  }
  if (cell.HasBottom()) {
    DrawBottomBorder(coordinates);
  }
  if (cell.HasLeft()) {
    DrawLeftBorder(coordinates);
  }
}

void GLWidget::DrawTopBorder(const CellCoordinates& coordinates) {
  glVertex2f(coordinates.top_left.x, coordinates.top_left.y);
  glVertex2f(coordinates.top_right.x, coordinates.top_right.y);
}

void GLWidget::DrawRightBorder(const CellCoordinates& coordinates) {
  glVertex2f(coordinates.top_right.x, coordinates.top_right.y);
  glVertex2f(coordinates.bottom_right.x, coordinates.bottom_right.y);
}

void GLWidget::DrawBottomBorder(const CellCoordinates& coordinates) {
  glVertex2f(coordinates.bottom_left.x, coordinates.bottom_left.y);
  glVertex2f(coordinates.bottom_right.x, coordinates.bottom_right.y);
}

void GLWidget::DrawLeftBorder(const CellCoordinates& coordinates) {
  glVertex2f(coordinates.top_left.x, coordinates.top_left.y);
  glVertex2f(coordinates.bottom_left.x, coordinates.bottom_left.y);
}

void GLWidget::DrawSolvingPath() {
  Maze::solving_path_type solving_path = maze_->GetSolvingPath();
  DrawSolvingPathPoints(solving_path);

  glLineWidth(2);
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  for (size_t i = 1; i < solving_path.size(); ++i) {
    Coordinates2D curent_coordinates = solving_path[i],
                       previos_coordinates = solving_path[i - 1];
    glVertex2f(curent_coordinates.x, curent_coordinates.y);
    glVertex2f(previos_coordinates.x, previos_coordinates.y);
  }
  glEnd();
}

void GLWidget::DrawSolvingPathPoints(
    const Maze::solving_path_type& solving_path) {
  glPointSize(10);
  glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  Coordinates2D last_cell = solving_path[0];
  Coordinates2D first_cell = solving_path[solving_path.size() - 1];
  glColor3f(1, 0, 0);
  glVertex2f(first_cell.x, first_cell.y);
  glColor3f(0, 0, 1);
  glVertex2f(last_cell.x, last_cell.y);
  glEnd();
}

void GLWidget::SetMaze(const Maze* maze) { maze_ = maze; }
