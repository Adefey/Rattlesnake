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
        if (names.count(blocks[i]->name) > 0) {
            names[blocks[i]->name] += 1;
        } else {
            names[blocks[i]->name] = 1;
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
        if (names.count(blocks[i - 1]->name) > 0) {
            int j = names[blocks[i - 1]->name];
            names[blocks[i - 1]->name] -= 1;
            std::string solver_path = blocks[i - 1]->solver_path;
            std::vector<Parameter> given_vars = blocks[i - 1]->given_vars;
            std::vector<Parameter> solved_vars = blocks[i - 1]->solved_vars;
            std::string name = blocks[i - 1]->name + "_" + std::to_string(j);
            std::string description = blocks[i - 1]->description;
            std::string author_name = blocks[i - 1]->author_name;
            int color = blocks[i - 1]->color;
            Block *new_block = new Block(
                solver_path, given_vars, solved_vars, name, description, author_name, color);
            delete blocks[i - 1];
            blocks[i - 1] = new_block;
            qDebug() << QString::fromStdString(blocks[i - 1]->name);
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
    QObject::connect(frame, SIGNAL(blockDeleted(std::string)), this, SLOT(deleteBlock(std::string)));
    return frame;
}

void SchemeWidget::deleteBlock(std::string name_to_delete) {
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i]->name == name_to_delete) {
            std::cout << "OK";
            delete blocks[i];
            break;
        }
    }
    emit schemeChanged();
}

void SchemeWidget::run(std::vector<Parameter>* parameters) {
    std::vector<Block> true_blocks;
    std::set<std::string> solved_parameters;
    for (size_t i = 0; i < blocks.size(); ++i) {
        std::vector<Parameter> given = (blocks[i])->given_vars;
        std::vector<Parameter> solved = (blocks[i])->solved_vars;
        for (size_t j = 0; j < given.size(); ++j) {
            given[j].param_name = (blocks[i])->name + "::" + given[j].param_name;
        }
        for (size_t j = 0; j < solved.size(); ++j) {
            solved[j].param_name = (blocks[i])->name + "::" + solved[j].param_name;
            solved_parameters.insert(solved[j].param_name);
        }
        Block bl = Block((blocks[i])->solver_path, given,
        solved, (blocks[i])->name, (blocks[i])->description, (blocks[i])->author_name, (blocks[i])->color);
        true_blocks.push_back(bl);
    }
    for (size_t i = 1; i < true_blocks.size(); ++i) {
        for (size_t j = 0; j < true_blocks[i].given_vars.size(); ++j) {
            for (size_t z = 0; z < parameters->size(); ++z) {
                if ((*parameters)[z].param_name == (true_blocks[i].given_vars)[j].param_name) {
                    if (solved_parameters.find((*parameters)[z].param_value) != solved_parameters.end()) {
                        true_blocks[i].given_vars[j].param_name = (*parameters)[z].param_value;
                    }
                }
            }
        }
        // std::string solver_path = true_blocks[i].GetSolverPath();
        // std::vector<Parameter> given_vars = true_blocks[i].GetGivenVars();
        // std::vector<Parameter> solved_vars = true_blocks[i].GetSolvedVars();
        // std::string name = true_blocks[i].GetName();
        // std::string description = true_blocks[i].GetDescription();
        // std::string author_name = true_blocks[i].GetAuthorName();
        // int color = true_blocks[i].GetColor();
        // Block new_block = Block(
        //         solver_path, true_params, solved_vars, name, description, author_name, color);
        // true_blocks[i] = new_block;
    }
    std::string jsonBlocks = Serializer::ToJsonString(true_blocks);

    std::cout << jsonBlocks << std::endl;

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
