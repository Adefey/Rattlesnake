#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    UI *ui = new UI(this);
    createTopToolBar();
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
    QAction *runAction = new QAction(this);
    QObject::connect(runAction, &QAction::triggered, this, &MainWindow::run);
    ptb->addAction(runAction);
}

void MainWindow::run() {
    qDebug() << "run";
}

MainWindow::~MainWindow()
{
}

