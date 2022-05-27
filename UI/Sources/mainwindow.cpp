#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createTopToolBar();
    UI *ui = new UI(this, runAction);
    addToolBar(Qt::TopToolBarArea, ptb);
    this->setAcceptDrops(false);
    ui->setAcceptDrops(false);
    setCentralWidget(ui);
}

void MainWindow::createTopToolBar()
{
    ptb = new QToolBar(this);

    QMenu *menu = new QMenu();
    create = new QAction("Создать", this);
    save = new QAction("Сохранить", this);
    open = new QAction("Открыть", this);
    ext = new QAction("Выход", this);
    QObject::connect(ext, &QAction::triggered, this, &MainWindow::end);
    menu->addAction(create);
    menu->addAction(save);
    menu->addAction(open);
    menu->addAction(ext);
    QToolButton* file = new QToolButton();
    file->setMenu(menu);
    file->setPopupMode(QToolButton::InstantPopup);
    file->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto act = new QAction();
    act->setText("Файл");
    file->setDefaultAction(act);
    file->setStyleSheet("QToolButton::menu-indicator{image:none;}");
    ptb->addWidget(file);
    runAction = new QAction(this);
    runAction->setIcon(QIcon(":/img/start-green-play-icon.png"));
    ptb->addAction(runAction);
}

void MainWindow::end() {
    this->close();
}