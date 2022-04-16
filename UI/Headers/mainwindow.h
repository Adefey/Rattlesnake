#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UI.h"
#include <QGridLayout>
#include <QMainWindow>
#include <QToolBar>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  QToolBar *createTopToolBar();

signals:
};

#endif // MAINWINDOW_H
