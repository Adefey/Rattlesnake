#ifndef QTLISTOFBLOCKS_H
#define QTLISTOFBLOCKS_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <qstring.h>
#include <QFrame>
#include <vector>
#include <string>
#include "block.hpp"
#include "blockwidget.h"
#include "newblockwidget.h"
#include "schemewidget.h"
#include "netlibraryclient.hpp"
#include "parser.hpp"

class QPaintEvent;

class QTListOfBlocks : public QWidget
{
    Q_OBJECT
public:
    QTListOfBlocks(QWidget *parent = nullptr, SchemeWidget *scheme = nullptr);
    virtual ~QTListOfBlocks() {};
    int get_list_of_blocks();

public slots:
    void updateWidgets();

private:
    NewBlockWidget* makeWidget(Block *block);
    QVBoxLayout *vbox;
    std::vector<Block> blocks;
    SchemeWidget *sch;

protected:
    void paintEvent(QPaintEvent*);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);

signals:
    void requestedBlocks();
};

#endif // QTLISTOFBLOCKS_H
