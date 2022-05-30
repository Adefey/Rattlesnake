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
    emit requestedBlocks(0);
    bool accessible_server = NetLibraryClient::SendBlocksRequest(sch->netClient);
    if (!accessible_server) {
        emit error(1);
        return 0;
    }
    std::string jsonBlocks;
    if (!NetLibraryClient::ReceiveBlocksJson(sch->netClient, jsonBlocks)) {
        emit error(2);
        return 0;
    }
    if (!Parser::ParseBlocksFromJsonString(jsonBlocks, blocks)) {
        return 0;
    }
    emit requestedBlocks(1);
    return 0;
}

NewBlockWidget* QTListOfBlocks::makeWidget(Block *block) {
    NewBlockWidget *frame = new NewBlockWidget(this, *block);
    QGridLayout *layout = new QGridLayout(frame);
    QLabel *name = new QLabel;
    name->setText(QString::fromStdString(block->name));
    name->setStyleSheet("QLabel { color : black; }");
    name->setAlignment(Qt::AlignCenter);
    for (size_t i = 0; i < block->given_vars.size(); ++i) {
        QLabel *givenVar = new QLabel;
        givenVar->setText(QString::fromStdString(block->given_vars[i].param_name));
        givenVar->setStyleSheet("QLabel { color : black; }");
        layout->addWidget(givenVar, i + 1, 0);
    }
    for (size_t i = 0; i < block->solved_vars.size(); ++i) {
        QLabel *givenVar = new QLabel;
        givenVar->setText(QString::fromStdString(block->solved_vars[i].param_name));
        givenVar->setStyleSheet("QLabel { color : black; }");
        layout->addWidget(givenVar, i + 1, 1);
    }
    layout->addWidget(name, 0, 0);
    frame->setMinimumWidth(300);
    frame->setMaximumWidth(300);
    frame->setMinimumHeight(150);
    frame->setToolTip(QString::fromStdString(block->description));
    int color = block->color;
    int red = (color & 0x00FF0000) >> 16;
    int green = (color & 0x0000FF00) >> 8;
    int blue = (color & 0x000000FF) >> 0;
    frame->setStyleSheet("background-color: rgb(" + QString::number(red) + ", " + QString::number(green) + ", " + QString::number(blue) + "); border: 2px solid black; color : black; ");
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

void QTListOfBlocks::dragEnterEvent(QDragEnterEvent* event) {
    event->ignore();
}

void QTListOfBlocks::dragMoveEvent(QDragMoveEvent* event) {
    event->ignore();
}

void QTListOfBlocks::dragLeaveEvent(QDragLeaveEvent* event) {
    event->ignore();
}
