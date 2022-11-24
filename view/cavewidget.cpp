#include "cavewidget.h"

CaveWidget::CaveWidget(QWidget* parent) : QGLWidget(parent) {}

void CaveWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
}

void CaveWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 500, 500, 0);
  glClearColor(1, 1, 1, 1);
  DrawCave();
}

void CaveWidget::DrawCave() {
  Matrix<CaveCell> cells = cave_->GetCells();
  glLineWidth(2);
  glPointSize(10);
  glBegin(GL_QUADS);
  glColor3f(0, 0, 0);
  for (Matrix<CaveCell>::size_type i = 0; i < cells.GetRows(); ++i) {
    for (Matrix<CaveCell>::size_type j = 0; j < cells.GetColumns();
         ++j) {
      if (cells(i, j).IsAlive()) {
        DrawCell(cells(i, j));
      }
    }
  }
  glEnd();
}

void CaveWidget::DrawCell(const CaveCell& cell) {
  CellCoordinates coordinates = cell.GetCoordinates();
  glVertex2i(coordinates.top_left.x, coordinates.top_left.y);
  glVertex2i(coordinates.top_right.x, coordinates.top_right.y);
  glVertex2i(coordinates.bottom_right.x, coordinates.bottom_right.y);
  glVertex2i(coordinates.bottom_left.x, coordinates.bottom_left.y);
}

void CaveWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0, (float)w / h, 0.01, 100.0);
  updateGL();
}

void CaveWidget::SetCave(const Cave* cave) { cave_ = cave; }
