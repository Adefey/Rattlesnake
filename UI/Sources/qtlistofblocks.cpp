#include "qtlistofblocks.h"

QTListOfBlocks::QTListOfBlocks(QWidget *parent, SchemeWidget *scheme) : QWidget(parent)
{
    sch = scheme;
    int res = get_list_of_blocks(&blocks);
    if (res) {
        return;
    }
    QVBoxLayout *mainlayout = new QVBoxLayout(parent);
    QWidget *w = new QWidget;
    vbox = new QVBoxLayout(w);
    vbox->setSpacing(20);
    vbox->setAlignment(Qt::AlignCenter);

    updateWidgets();

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(w);
    mainlayout->addWidget(scrollArea);
}

void QTListOfBlocks::updateWidgets() {
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

int QTListOfBlocks::get_list_of_blocks(std::vector<Block>* blocks)
{
    emit requestedBlocks();
    Block *block1 = new Block;
    Block *block2 = new Block;
    Block *block3 = new Block;
    block1->name = "block1";
    block2->name = "block2";
    block3->name = "block3";
    Parameter par1 = {"var1", "val1"};
    Parameter par2 = {"var2", "val2"};
    Parameter par3 = {"var3", "val3"};
    block1->given_vars.push_back(par1);
    block1->color = 3;
    block1->given_vars.push_back(par2);
    block2->given_vars.push_back(par2);
    block2->given_vars.push_back(par3);
    block3->given_vars.push_back(par1);
    block3->given_vars.push_back(par2);
    block3->given_vars.push_back(par3);
    block3->given_vars.push_back(par3);
    block1->solved_vars.push_back(par1);
    block1->solved_vars.push_back(par2);
    block2->solved_vars.push_back(par2);
    block3->solved_vars.push_back(par1);
    block3->solved_vars.push_back(par2);
    block3->solved_vars.push_back(par3);
    blocks->push_back(*block1);
    blocks->push_back(*block2);
    blocks->push_back(*block3);
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
        givenVar->setText(QString::fromStdString(block->given_vars[i].var_name));
        layout->addWidget(givenVar, i + 1, 0);
    }
    for (size_t i = 0; i < block->solved_vars.size(); ++i) {
        QLabel *givenVar = new QLabel;
        givenVar->setText(QString::fromStdString(block->solved_vars[i].var_name));
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
