#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QToolBar>
#include <QMenu>
#include <QToolButton>
#include <QWidgetAction>
#include "UI.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolBar *ptb;
    QMenu *filemenu;

public slots:
    void end();

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() {};
    void createTopToolBar();
    QAction *runAction;
    QAction *create;
    QAction *save;
    QAction *open;
    QAction *ext;
};
#endif // MAINWINDOW_H
