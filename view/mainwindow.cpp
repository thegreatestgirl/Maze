#include "mainwindow.h"

#include <QCloseEvent>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixelFormat>
#include <QTime>
#include <QTimer>
#include <iostream>

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  const Maze* maze = controller_.GetMazeReference();
  ui->GLwidget->SetMaze(maze);

  const Cave* cave = controller_.GetCaveReference();
  ui->Cavewidget->SetCave(cave);

  timer = new QTimer(this);

  ConnectMazeButtons();
  ConnectCaveButtons();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_generate_maze_clicked() {
  controller_.GenerateMaze(ui->maze_rows->value(), ui->maze_columns->value());
}

void MainWindow::on_save_maze_to_file_clicked() {
  QDateTime current_date_time = QDateTime::currentDateTime();
  long long seconds = current_date_time.toSecsSinceEpoch();
  QString path = QDir::homePath() + "/" + QString::number(seconds) + ".txt";
  controller_.SaveMazeToFile(path.toStdString());
  ShowMessageBox("Файл с лабиринтом сохранен по пути: " + path);
}

void MainWindow::on_solve_maze_clicked() {
  try {
    controller_.SolveMaze(this->ui->i1->value(), this->ui->j1->value(),
                          this->ui->i2->value(), this->ui->j2->value());
  } catch (InvalidCellCoordinates&) {
    ShowMessageBox("Некорректные координаты ячеек");
  } catch (MazeSolutionDoesNotExists&) {
    ShowMessageBox("Пути между данными ячейками не существует");
  }
}

void MainWindow::on_load_maze_clicked() {
  QString filter = "Maze file (*.txt)";
  QString file_name = QFileDialog::getOpenFileName(this, "Open a file",
                                                   QDir::homePath(), filter);
  std::string file_path = file_name.toStdString();
  if (!file_name.isEmpty()) {
    try {
      controller_.LoadMazeFromFile(file_path);
    } catch (InvalidMaze&) {
      ShowMessageBox("Некорректный лабиринт");
    }
  }
}

void MainWindow::ShowMessageBox(const QString text) {
  QMessageBox success_maeeage_box;
  success_maeeage_box.setText(text);
  success_maeeage_box.exec();
}

void MainWindow::on_update_cave_clicked() {
  controller_.UpdateCave(ui->born_limit->value(), ui->death_limit->value());
}

void MainWindow::on_load_cave_clicked() {
  QString filter = "Cave file (*.txt)";
  QString file_name = QFileDialog::getOpenFileName(this, "Open a file",
                                                   QDir::homePath(), filter);
  std::string file_path = file_name.toStdString();
  if (!file_name.isEmpty()) {
    try {
      controller_.LoadCaveFromFile(file_path);
    } catch (InvalidCave&) {
      ShowMessageBox("Некорректная пещера");
    }
  }
}

void MainWindow::on_generate_cave_clicked() {
  controller_.GenerateCave(ui->cave_rows->value(), ui->cave_columns->value());
}

void MainWindow::on_cave_initialize_chance_valueChanged(int value) {
  controller_.SetInitializeChance(value);
}

void MainWindow::update_cave() {
  controller_.UpdateCave(ui->born_limit->value(), ui->death_limit->value());
  ui->Cavewidget->update();
}

void MainWindow::on_start_updating_cave_clicked() {
  timer->setInterval(ui->cave_update_time->value());
  timer->start();
}

void MainWindow::on_stop_updating_cave_clicked() { timer->stop(); }

void MainWindow::ConnectMazeButtons() {
  //    connect(ui->generate_maze, SIGNAL(clicked()), this->ui->GLwidget,
  //    SLOT(update())); connect(ui->solve_maze, SIGNAL(clicked()),
  //    this->ui->GLwidget, SLOT(update())); connect(ui->load_maze,
  //    SIGNAL(clicked()), this->ui->GLwidget, SLOT(update()));
  connect(ui->generate_maze, SIGNAL(clicked()), this->ui->GLwidget,
          SLOT(updateGL()));
  connect(ui->solve_maze, SIGNAL(clicked()), this->ui->GLwidget,
          SLOT(updateGL()));
  connect(ui->load_maze, SIGNAL(clicked()), this->ui->GLwidget,
          SLOT(updateGL()));
}

void MainWindow::ConnectCaveButtons() {
  connect(timer, SIGNAL(timeout()), this, SLOT(update_cave()));
  //    connect(ui->update_cave, SIGNAL(clicked()), this->ui->Cavewidget,
  //    SLOT(update())); connect(ui->load_cave, SIGNAL(clicked()),
  //    this->ui->Cavewidget, SLOT(update())); connect(ui->generate_cave,
  //    SIGNAL(clicked()), this->ui->Cavewidget, SLOT(update()));
  connect(ui->update_cave, SIGNAL(clicked()), this->ui->Cavewidget,
          SLOT(updateGL()));
  connect(ui->load_cave, SIGNAL(clicked()), this->ui->Cavewidget,
          SLOT(updateGL()));
  connect(ui->generate_cave, SIGNAL(clicked()), this->ui->Cavewidget,
          SLOT(updateGL()));
}
