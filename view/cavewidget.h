#ifndef CAVEWIDGET_H
#define CAVEWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <QGLWidget>

#include "../model/cave.h"
#include "../model/exceptions.h"

class CaveWidget : public QGLWidget {
  Q_OBJECT

 public:
  explicit CaveWidget(QWidget* parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

 private:
  const Cave* cave_;

 public:
  void SetCave(const Cave* cave);

 private:
  void DrawCave();
  void DrawCell(const CaveCell& cell);
};

#endif  // CAVEWIDGET_H
