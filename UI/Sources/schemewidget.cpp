#include "schemewidget.h"

SchemeWidget::SchemeWidget(QWidget *parent) : QWidget(parent)
{
    std::string ip = AppInfo::GetIP();
    if (ip == "ERROR") {
        QMessageBox::warning(this, "Ошибка", "Не найден файл cfg.txt");
        QCoreApplication::quit();
    }
    netClient.SetServerAddress(ip.c_str(), AppInfo::GetPort());
    QHBoxLayout *mainlayout = new QHBoxLayout(parent);
    w = new QWidget(this);
    vbox = new QVBoxLayout(w);
    vbox->setSpacing(20);
    vbox->setAlignment(Qt::AlignCenter);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(w);
    scrollArea->setWidgetResizable(true);
    mainlayout->addWidget(scrollArea);
    this->setAcceptDrops(true);
    QObject::connect(this, SIGNAL(schemeChanged()), this, SLOT(updateWidgets()));
}

void SchemeWidget::addBlock(Block *block) {
    blocks.push_back(block);
    BlockWidget *widget = makeWidget(block);
    vbox->addWidget(widget);
    correctNames();
}

void SchemeWidget::correctNames() {
    std::map<std::string, int> names;
    for (size_t i = 0; i < blocks.size(); ++i) {
        int pos = findCounter(blocks[i]->name);
        if (pos != 0) {
            blocks[i]->name = blocks[i]->name.substr(0, pos);
        }
    }
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
            blocks[i - 1]->name = blocks[i - 1]->name + "_" + std::to_string(j);
        }
    }
    emit schemeChanged();
}

int SchemeWidget::findCounter(const std::string str) {
    int pos = 0;
    for (int i = str.size() - 1; i >= 0; --i) {
        if (str[i] == '_') {
            pos = i;
            break;
        }
    }
    if (pos == 0) {
        return 0;
    }
    std::string subString = str.substr(pos + 1, str.size() - pos - 1);
    for (int i = 0; i < subString.size(); ++i) {
        if (!isdigit(subString.at(i))) {
            return 0;
        }
    }
    return pos;
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
        widget->pos = i;
        vbox->addWidget(widget);
    }
    emit updateSignal(&blocks);
}

BlockWidget* SchemeWidget::makeWidget(Block *block) {
    BlockWidget *frame = new BlockWidget(this, block);
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
    frame->setStyleSheet("background-color: rgb(" + QString::number(red) + ", " + QString::number(green) + ", " + QString::number(blue) + "); border: 2px solid black; color : black;");
    frame->setFrameShape(QFrame::StyledPanel);
    QObject::connect(frame, SIGNAL(blockDeleted(BlockWidget*)), this, SLOT(deleteBlock(BlockWidget*)));
    return frame;
}

void SchemeWidget::deleteBlock(BlockWidget* blockToDelete) {
    std::vector<Block*> newBlocks;
    std::cout << "2" << std::endl;
    blocks = newBlocks;
    std::cout << "3" << std::endl;
    vbox->removeWidget(blockToDelete);
    std::cout << "4" << std::endl;
    correctNames();
    std::cout << "5" << std::endl;
}

void SchemeWidget::clear() {
    if ( vbox != NULL )
    {
        QLayoutItem* item;
        while ( ( item = vbox->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
    blocks.clear();
}

void SchemeWidget::run(std::vector<Parameter>* parameters) {
    if (blocks.size() == 0) {
        emit errorAppeared(5);
        return;
    }
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
        Block newBlock = Block(blocks[i]->solver_path, given,
        solved, blocks[i]->name, blocks[i]->description,
        blocks[i]->author_name, blocks[i]->color);
        true_blocks.push_back(newBlock);
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
    }
    std::string jsonBlocks = Serializer::ToJsonString(true_blocks);

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
    event->accept();
}

void SchemeWidget::dropEvent(QDropEvent* event) {
    event->acceptProposedAction();
    event->setAccepted(acceptDrops());
}

void SchemeWidget::dragEnterEvent(QDragEnterEvent* event) {
    event->acceptProposedAction();
}

void SchemeWidget::dragLeaveEvent(QDragLeaveEvent* event) {
    event->accept();
}

bool SchemeWidget::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Drop) {
        QDropEvent *de = static_cast<QDropEvent*>(event);
        de->acceptProposedAction();
        return true;
    }
    else if (event->type() == QEvent::DragEnter) {
        QDragEnterEvent *dee = static_cast<QDragEnterEvent*>(event);
        dee->acceptProposedAction();
        return true;
    }
    return false;
}
