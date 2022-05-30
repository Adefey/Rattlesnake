#include "splitter.h"

Splitter::Splitter(QWidget* parent, QAction* runAction) : QWidget(parent) {
    QHBoxLayout* hbox = new QHBoxLayout(this);

    QWidget* scheme = new QWidget;
    scheme->acceptDrops();
    scheme->setAcceptDrops(true);

    QWidget* requiredVariables = new QWidget;
    RequiredVariables* reqv = new RequiredVariables(requiredVariables);
    requiredVariables->adjustSize();

    QWidget* lg = new QWidget;
    LogWidget* log = new LogWidget(lg);

    QSplitter* Hsplitter = new QSplitter(Qt::Vertical);

    QWidget* listofblocks = new QWidget;
    SchemeWidget* sch = new SchemeWidget(scheme);
    sch->acceptDrops();
    sch->setAcceptDrops(true);
    qApp->installEventFilter(sch);
    QTListOfBlocks* lstblks = new QTListOfBlocks(listofblocks, sch);
    QSplitter* Vsplitter = new QSplitter(Qt::Horizontal);

    QObject::connect(sch, SIGNAL(updateSignal(std::vector<Block*>*)), reqv,
                     SLOT(updateTable(std::vector<Block*>*)));
    QObject::connect(lstblks, SIGNAL(requestedBlocks(int)), log,
                     SLOT(sayRequestedBlocks(int)));
    QObject::connect(runAction, &QAction::triggered, reqv,
                     &RequiredVariables::run);
    QObject::connect(reqv, SIGNAL(send(std::vector<Parameter>*)), sch,
                     SLOT(run(std::vector<Parameter>*)));
    QObject::connect(sch, SIGNAL(resultsRecieved(std::string)), log,
                     SLOT(answer(std::string)));
    QObject::connect(lstblks, SIGNAL(error(int)), log, SLOT(errorLog(int)));
    QObject::connect(sch, SIGNAL(errorAppeared(int)), log, SLOT(errorLog(int)));
    QObject::connect(sch, SIGNAL(schemeSent()), log, SLOT(schemeSent()));
    QObject::connect(log, SIGNAL(updateTable(const std::vector<Parameter>&)),
                     reqv, SLOT(updateAnswers(const std::vector<Parameter>&)));
    QObject::connect(this, SIGNAL(create()), reqv, SLOT(clear()));
    QObject::connect(this, SIGNAL(create()), sch, SLOT(clear()));
    QObject::connect(this, SIGNAL(save()), sch, SLOT(save()));
    QObject::connect(sch, SIGNAL(saving(std::string&)), reqv,
                     SLOT(save(std::string&)));
    QObject::connect(this, SIGNAL(openscheme(std::string&, std::string&)), sch,
                     SLOT(open(std::string&, std::string&)));
    QObject::connect(sch, SIGNAL(openvars(std::string&)), reqv,
                     SLOT(open(std::string&)));

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

void Splitter::open() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Project"), "", tr("Rattlesnake Project (*.rtlsnk);"));
    if (fileName.isEmpty()) {
        return;
    } else {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        QString data;
        in >> data;
        if (data.isEmpty()) {
            QMessageBox::information(this, tr("Project is empty"),
                                     tr("The file you are attempting to open "
                                        "contains no information."));
        } else {
            std::string datastd = data.toStdString();
            std::string datascheme;
            std::string datareqv;
            parseOpenFile(datastd, datascheme, datareqv);
            emit openscheme(datascheme, datareqv);
        }
    }
}

void Splitter::parseOpenFile(std::string& data, std::string& datascheme,
                             std::string& datareqv) {
    size_t i = 0;
    while (data[i] != '#') {
        datascheme += data[i++];
    }
    i += 10;
    datareqv = data.substr(i, data.size() - i);
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
