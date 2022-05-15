#include "qtlistofblocks.h"

QTListOfBlocks::QTListOfBlocks(QWidget *parent, SchemeWidget *scheme) : QWidget(parent)
{
    sch = scheme;
    button = new QPushButton("Получить блоки");

    QVBoxLayout *mainlayout = new QVBoxLayout(parent);
    QWidget *w = new QWidget;
    vbox = new QVBoxLayout(w);
    vbox->setSpacing(20);
    vbox->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(button);
    QObject::connect(button, SIGNAL (released()), this, SLOT (handleButton()));

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(w);
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable(true);
    mainlayout->addWidget(scrollArea);
}

void QTListOfBlocks::updateWidgets() {
    vbox->update();
    if ( vbox != NULL )
    {
        QLayoutItem* item;
        while ( ( item = vbox->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
    for (size_t i = 0; i < blocks.size(); ++i) {
        NewBlockWidget *widget = makeWidget(&(blocks[i]));
        vbox->addWidget(widget);
        QObject::connect(widget, SIGNAL(blockPressed(Block*)), sch, SLOT(addBlock(Block*)));
    }
}

int QTListOfBlocks::get_list_of_blocks()
{
    emit requestedBlocks();
    std::cout << "1" << std::endl;
    bool accessible_server = NetLibraryClient::SendBlocksRequest(sch->netClient);
    std::cout << "2" << std::endl;
    if (!accessible_server) {
        emit error(1);
        return 0;
    }
    std::cout << "3" << std::endl;
    std::string jsonBlocks;
    if (!NetLibraryClient::ReceiveBlocksJson(sch->netClient, jsonBlocks)) {
        emit error(2);
        return 0;
    }
    std::cout << "4" << std::endl;
    if (!Parser::ParseBlocksFromJsonString(jsonBlocks, blocks)) {
        return 0;
    }
    std::cout << "5" << std::endl;
    return 0;
}

NewBlockWidget* QTListOfBlocks::makeWidget(Block *block) {
    NewBlockWidget *frame = new NewBlockWidget(this, *block);
    QGridLayout *layout = new QGridLayout(frame);
    QLabel *name = new QLabel;
    name->setText(QString::fromStdString(block->GetName()));
    name->setAlignment(Qt::AlignCenter);
    for (size_t i = 0; i < block->GetGivenVars().size(); ++i) {
        QLabel *givenVar = new QLabel;
        givenVar->setText(QString::fromStdString(block->GetGivenVars()[i].param_name));
        layout->addWidget(givenVar, i + 1, 0);
    }
    for (size_t i = 0; i < block->GetSolvedVars().size(); ++i) {
        QLabel *givenVar = new QLabel;
        givenVar->setText(QString::fromStdString(block->GetSolvedVars()[i].param_name));
        layout->addWidget(givenVar, i + 1, 1);
    }
    layout->addWidget(name, 0, 0);
    frame->setMinimumWidth(200);
    frame->setMaximumWidth(200);
    frame->setMinimumHeight(100);
    frame->setStyleSheet("background-color: #b3b3b3; border: 2px solid black");
    frame->setFrameShape(QFrame::StyledPanel);
    return frame;
}

void QTListOfBlocks::handleButton() {
    blocks.clear();
    int res = get_list_of_blocks();
    if (res) {
        return;
    }
    updateWidgets();
}

void QTListOfBlocks::paintEvent(QPaintEvent*) {
    QPainter p(this);
}

void QTListOfBlocks::dragEnterEvent(QDragEnterEvent* event) {
    event->ignore();
}

void QTListOfBlocks::dragMoveEvent(QDragMoveEvent* event) {
    event->ignore();
}

void QTListOfBlocks::dragLeaveEvent(QDragLeaveEvent* event) {
    event->ignore();
}
