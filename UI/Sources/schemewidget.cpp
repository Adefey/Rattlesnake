#include "schemewidget.h"

SchemeWidget::SchemeWidget(QWidget *parent) : QWidget(parent)
{
    netClient.SetServerAddress("127.0.0.1", 8000);
    QHBoxLayout *mainlayout = new QHBoxLayout(parent);
    QWidget *w = new QWidget(this);
    vbox = new QVBoxLayout(w);
    vbox->setSpacing(20);
    vbox->setAlignment(Qt::AlignCenter);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(w);
    scrollArea->setWidgetResizable(true);
    mainlayout->addWidget(scrollArea);
    parent->setAcceptDrops(true);
    this->setAcceptDrops(true);
    QObject::connect(this, SIGNAL(schemeChanged()), this, SLOT(updateWidgets()));
}

void SchemeWidget::addBlock(Block *block) {
    if (vbox->geometry().contains(QCursor::pos())) { return; }
    blocks.push_back(block);
    BlockWidget *widget = makeWidget(block);
    vbox->addWidget(widget);
    correctNames();
}

void SchemeWidget::correctNames() {
    std::map<std::string, int> names;
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (names.count(blocks[i]->GetName()) > 0) {
            names[blocks[i]->GetName()] += 1;
        } else {
            names[blocks[i]->GetName()] = 1;
        }
    }
    auto it = names.begin();
    while (it != names.end()) {
        if (it->second == 1) {
           it = names.erase(it);
        } else {
           ++it;
        }
    }
    for (int i = blocks.size(); i >= 1 && blocks.size() > 1; --i) {
        if (names.count(blocks[i - 1]->GetName()) > 0) {
            int j = names[blocks[i - 1]->GetName()];
            names[blocks[i - 1]->GetName()] -= 1;
            std::string solver_path = blocks[i - 1]->GetSolverPath();
            std::vector<Parameter> given_vars = blocks[i - 1]->GetGivenVars();
            std::vector<Parameter> solved_vars = blocks[i - 1]->GetSolvedVars();
            std::string name = blocks[i - 1]->GetName();
            std::string description = blocks[i - 1]->GetDescription();
            std::string author_name = blocks[i - 1]->GetAuthorName();
            int color = blocks[i - 1]->GetColor();
            Block *new_block = new Block(
                solver_path, given_vars, solved_vars, name, description, author_name, color);
            delete blocks[i - 1];
            blocks[i - 1] = new_block;
            qDebug() << QString::fromStdString(blocks[i - 1]->GetName());
        }
    }
    emit schemeChanged();
}

void SchemeWidget::updateWidgets() {
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
        BlockWidget *widget = makeWidget(blocks[i]);
        vbox->addWidget(widget);
    }
    emit updateSignal(&blocks);
}

BlockWidget* SchemeWidget::makeWidget(Block *block) {
    BlockWidget *frame = new BlockWidget(this);
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

void SchemeWidget::run(std::vector<Parameter>* parameters) {
    std::vector<Block> true_blocks;
    for (size_t i = 0; i < blocks.size(); ++i) {
        std::vector<Parameter> given = (blocks[i])->GetGivenVars();
        std::vector<Parameter> solved = (blocks[i])->GetSolvedVars();
        for (size_t j = 0; j < given.size(); ++j) {
            given[j].param_name = /*(blocks[i])->GetName() + "::" + */given[j].param_name;
        }
        for (size_t j = 0; j < solved.size(); ++j) {
            solved[j].param_name = /*(blocks[i])->GetName() + "::" + */solved[j].param_name;
        }
        Block bl = Block((blocks[i])->GetSolverPath(), given,
        solved, (blocks[i])->GetName(), (blocks[i])->GetDescription(), (blocks[i])->GetAuthorName(), (blocks[i])->GetColor());
        true_blocks.push_back(bl);
    }
    std::string jsonBlocks = Serializer::ToJsonString(true_blocks);

    // std::cout << jsonBlocks << std::endl;

    std::vector<Parameter> true_parameters = *parameters;
    std::string jsonParams = Serializer::ToJsonString(true_parameters);
    if (!NetLibraryClient::SendSchemeJson(netClient, jsonBlocks, jsonParams)) {
        emit errorAppeared(3);
        return;
    }
    //emit schemeSent();
    std::string result;
    if (!NetLibraryClient::ReceiveResultsJson(netClient, result)) {
        emit errorAppeared(4);
        return;
    }
    emit resultsRecieved(result);
}

void SchemeWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
}

void SchemeWidget::dragMoveEvent(QDragMoveEvent* event) {
//    if (event->mimeData()->hasFormat("qt-class/qcolor"))
    qDebug() << "OK";
//    event->accept();
    event->acceptProposedAction();
//    event->setAccepted(acceptDrops());
}

void SchemeWidget::dragEnterEvent(QDragEnterEvent* event) {
//    if (event->mimeData()->hasFormat("qt-class/qcolor"))
    qDebug() << "OK";
//    event->accept();
    event->acceptProposedAction();
//    event->setAccepted(acceptDrops());
}

void SchemeWidget::dragLeaveEvent(QDragLeaveEvent* event) {
    qDebug() << "OK";
    event->accept();
}

bool SchemeWidget::eventFilter(QObject *obj, QEvent *event) {
    qDebug() << "OK";
    if (event->type() == QEvent::DragEnter) {
        QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent*>(event);
        dee->acceptProposedAction();
        return true;
    }
}

void SchemeWidget::dropEvent(QDropEvent *event) {

}
