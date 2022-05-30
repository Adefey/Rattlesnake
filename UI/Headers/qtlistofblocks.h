#ifndef QTLISTOFBLOCKS_H
#define QTLISTOFBLOCKS_H

#include <qstring.h>

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <string>
#include <vector>

#include "block.hpp"
#include "blockwidget.h"
#include "netlibraryclient.hpp"
#include "newblockwidget.h"
#include "parser.hpp"
#include "schemewidget.h"

class QTListOfBlocks : public QWidget {
    Q_OBJECT
   public:
    QTListOfBlocks(QWidget* parent = nullptr, SchemeWidget* scheme = nullptr);
    virtual ~QTListOfBlocks() {}
    int get_list_of_blocks();

   public slots:
    void updateWidgets();
    void handleButton();

   private:
    NewBlockWidget* makeWidget(Block* block);
    QVBoxLayout* vbox;
    std::vector<Block> blocks;
    SchemeWidget* sch;
    QPushButton* button;

   protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);

   signals:
    void requestedBlocks(int);
    void error(int);
};

#endif  // QTLISTOFBLOCKS_H
