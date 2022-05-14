#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QToolBar>
#include <QMenu>
#include <QToolButton>
#include "UI.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolBar *ptb;

public slots:
    void run();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createTopToolBar();
};
#endif // MAINWINDOW_H
