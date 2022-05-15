#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createTopToolBar();
    UI *ui = new UI(this, runAction);
    addToolBar(Qt::TopToolBarArea, ptb);
    setCentralWidget(ui);
}

void MainWindow::createTopToolBar()
{
    ptb = new QToolBar;
    ptb->addAction("Файл");
    ptb->addAction("Правка");
    ptb->addAction("Вид");
    ptb->addAction("Справка");

//    QMenu *menu = new QMenu();
//    QAction *testAction = new QAction("Запуск", this);
//    menu->addAction(testAction);

//    QToolButton* toolButton = new QToolButton();
//    toolButton->setMenu(menu);
//    toolButton->setPopupMode(QToolButton::InstantPopup);
//    ptb->addWidget(toolButton);
    runAction = new QAction(this);
    ptb->addAction(runAction);
}

