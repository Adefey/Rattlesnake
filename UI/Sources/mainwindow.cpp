#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QGridLayout *mainlayout = new QGridLayout(this);

    Splitter *splitter = new Splitter(this);
    mainlayout->addWidget(splitter);
    addToolBar(Qt::TopToolBarArea, createTopToolBar());
    setCentralWidget(splitter);
}

QToolBar* MainWindow::createTopToolBar()
{
    QToolBar *ptb = new QToolBar;
    ptb->addAction("Файл", this, SLOT(slotNoImpl()));
    ptb->addAction("Правка", this, SLOT(slotNoImpl()));
    ptb->addAction("Вид", this, SLOT(slotNoImpl()));
    ptb->addAction("Справка", this, SLOT(slotNoImpl()));
    return ptb;
}
