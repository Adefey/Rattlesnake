#include "splitter.h"

Splitter::Splitter(QWidget *parent, QAction *runAction)
    : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    QWidget *scheme = new QWidget;
    scheme->acceptDrops();
    scheme->setAcceptDrops(true);

    QWidget *requiredVariables = new QWidget;
    RequiredVariables *reqv = new RequiredVariables(requiredVariables);
    requiredVariables->adjustSize();

    QWidget *lg = new QWidget;
    LogWidget *log = new LogWidget(lg);

    QSplitter *Hsplitter = new QSplitter(Qt::Vertical);

    QWidget *listofblocks = new QWidget;
    SchemeWidget *sch = new SchemeWidget(scheme);
    sch->acceptDrops();
    sch->setAcceptDrops(true);
    qApp->installEventFilter(sch);
    QTListOfBlocks *lstblks = new QTListOfBlocks(listofblocks, sch);
    QSplitter *Vsplitter = new QSplitter(Qt::Horizontal);

    QObject::connect(sch, SIGNAL(updateSignal(std::vector<Block*>*)), reqv, SLOT(updateTable(std::vector<Block*>*)));
    QObject::connect(lstblks, SIGNAL(requestedBlocks(int)), log, SLOT(sayRequestedBlocks(int)));
    QObject::connect(runAction, &QAction::triggered, reqv, &RequiredVariables::run);
    QObject::connect(reqv, SIGNAL(send(std::vector<Parameter>*)), sch, SLOT(run(std::vector<Parameter>*)));
    QObject::connect(sch, SIGNAL(resultsRecieved(std::string)), log, SLOT(answer(std::string)));
    QObject::connect(lstblks, SIGNAL(error(int)), log, SLOT(errorLog(int)));
    QObject::connect(sch, SIGNAL(errorAppeared(int)), log, SLOT(errorLog(int)));
    QObject::connect(sch, SIGNAL(schemeSent()), log, SLOT(schemeSent()));
    QObject::connect(log, SIGNAL(updateTable(const std::vector<Parameter>&)), reqv, SLOT(updateAnswers(const std::vector<Parameter>&)));
    QObject::connect(this, SIGNAL(create()), reqv, SLOT(clear()));
    QObject::connect(this, SIGNAL(create()), sch, SLOT(clear()));

    Hsplitter->addWidget(scheme);
    Hsplitter->addWidget(lg);
    QList<int> sizes1({800, 200});
    Hsplitter->setSizes(sizes1);

    Vsplitter->addWidget(listofblocks);
    Vsplitter->addWidget(Hsplitter);
    Vsplitter->addWidget(requiredVariables);

    QList<int> sizes2({300, 800, 400});
    Vsplitter->setSizes(sizes2);

    hbox->addWidget(Vsplitter);

    this->setAcceptDrops(false);
}

void Splitter::dragEnterEvent(QDragEnterEvent* event) {
    event->ignore();
}

void Splitter::dragMoveEvent(QDragMoveEvent* event) {
    event->ignore();
}

void Splitter::dragLeaveEvent(QDragLeaveEvent* event) {
    event->ignore();
}
