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

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() {};
    void createTopToolBar();
    QAction *runAction;
};
#endif // MAINWINDOW_H
