#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_generate_maze_clicked();
  void on_save_maze_to_file_clicked();
  void on_solve_maze_clicked();
  void on_load_maze_clicked();
  void on_update_cave_clicked();
  void on_load_cave_clicked();
  void on_generate_cave_clicked();
  void on_cave_initialize_chance_valueChanged(int value);
  void update_cave();
  void on_start_updating_cave_clicked();
  void on_stop_updating_cave_clicked();

 private:
  Ui::MainWindow *ui;
  Controller controller_;
  QTimer *timer;

 private:
  void ShowMessageBox(const QString text);
  void ConnectMazeButtons();
  void ConnectCaveButtons();
};

#endif  // MAINWINDOW_H
