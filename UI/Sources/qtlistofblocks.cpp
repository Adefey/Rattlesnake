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

// std::string solver_path_;
//   std::vector<Parameter> given_vars_;
//   std::vector<Parameter> solved_vars_;
//   std::string name_;
//   std::string description_;
//   std::string author_name_;
//   int color_;

int QTListOfBlocks::get_list_of_blocks()
{
    // emit requestedBlocks(0);
    
    // Parameter par1 = {"in1", "val1"};
    // Parameter par2 = {"in2", "val2"};
    // Parameter par3 = {"in3", "val3"};
    // Parameter par11 = {"out1", "val1"};
    // Parameter par21 = {"out2", "val2"};
    // Parameter par31 = {"out3", "val3"};
    // std::vector<Parameter> given_vars1 = {par1, par2};
    // std::vector<Parameter> given_vars2 = {par2};
    // std::vector<Parameter> given_vars3 = {par1, par2, par3};
    // std::vector<Parameter> out_vars1 = {par11, par31};
    // std::vector<Parameter> out_vars2 = {par21, par31};
    // std::vector<Parameter> out_vars3 = {par11, par21};


    // Block block1 = Block("path", given_vars1, out_vars1, "name_of_block", "blo", "poh", 14474495);
    // Block block2 = Block("path", given_vars2, out_vars2, "Pupa", "blo", "poh", 16768220);
    // Block block3 = Block("path", given_vars3, out_vars3, "Lupa", "blo", "poh", 14483420);
    // blocks.push_back(block1);
    // blocks.push_back(block2);
    // blocks.push_back(block3);
    
    // emit requestedBlocks(0);
    // return 0;

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
    name->setAlignment(Qt::AlignCenter);
    for (size_t i = 0; i < block->given_vars.size(); ++i) {
        QLabel *givenVar = new QLabel;
        givenVar->setText(QString::fromStdString(block->given_vars[i].param_name));
        layout->addWidget(givenVar, i + 1, 0);
    }
    for (size_t i = 0; i < block->solved_vars.size(); ++i) {
        QLabel *givenVar = new QLabel;
        givenVar->setText(QString::fromStdString(block->solved_vars[i].param_name));
        layout->addWidget(givenVar, i + 1, 1);
    }
    layout->addWidget(name, 0, 0);
    frame->setMinimumWidth(200);
    frame->setMaximumWidth(200);
    frame->setMinimumHeight(100);
    int color = block->color;
    int red = (color & 0x00FF0000) >> 16;
    int green = (color & 0x0000FF00) >> 8;
    int blue = (color & 0x000000FF) >> 0;
    frame->setStyleSheet("background-color: rgb(" + QString::number(red) + ", " + QString::number(green) + ", " + QString::number(blue) + "); border: 2px solid black");
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
