#include "splitter.h"

Splitter::Splitter(QWidget *parent, QAction *runAction)
    : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    QWidget *scheme = new QWidget;
    scheme->acceptDrops();

    QWidget *requiredVariables = new QWidget;
    RequiredVariables *reqv = new RequiredVariables(requiredVariables);
    requiredVariables->adjustSize();

    QWidget *lg = new QWidget;
    LogWidget *log = new LogWidget(lg);

    QSplitter *Hsplitter = new QSplitter(Qt::Vertical);

    QWidget *listofblocks = new QWidget;
    SchemeWidget *sch = new SchemeWidget(scheme);
    QTListOfBlocks *lstblks = new QTListOfBlocks(listofblocks, sch);
    //listofblocks->setFrameShape(QFrame::StyledPanel);
    QSplitter *Vsplitter = new QSplitter(Qt::Horizontal);

    QObject::connect(sch, SIGNAL(updateSignal(std::vector<Block*>*)), reqv, SLOT(updateTable(std::vector<Block*>*)));
    QObject::connect(lstblks, SIGNAL(requestedBlocks()), log, SLOT(sayRequestedBlocks()));
    QObject::connect(runAction, &QAction::triggered, reqv, &RequiredVariables::run);
    QObject::connect(reqv, SIGNAL(send(std::vector<Parameter>*)), sch, SLOT(run(std::vector<Parameter>*)));
    QObject::connect(sch, SIGNAL(resultsRecieved(std::string)), log, SLOT(answer(std::string)));

    Hsplitter->addWidget(requiredVariables);
    Hsplitter->addWidget(scheme);
    Hsplitter->addWidget(lg);
    QList<int> sizes1({500, 800, 200});
    Hsplitter->setSizes(sizes1);

    Vsplitter->addWidget(listofblocks);
    Vsplitter->addWidget(Hsplitter);

    QList<int> sizes2({200, 1000});
    Vsplitter->setSizes(sizes2);

    hbox->addWidget(Vsplitter);
}

void Splitter::dragEnterEvent(QDragEnterEvent* event) {
    event->acceptProposedAction();
}

void Splitter::dragMoveEvent(QDragMoveEvent* event) {
    event->accept();
}

void Splitter::dragLeaveEvent(QDragLeaveEvent* event) {
    event->accept();
}
