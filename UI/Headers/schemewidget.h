#ifndef SCHEME_H
#define SCHEME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <qstring.h>
#include <QLabel>
#include <vector>
#include <map>
#include <QDebug>
#include <QMetaObject>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include "block.hpp"
#include "blockwidget.h"
#include "newblockwidget.h"
#include "netclient.hpp"
#include "netlibraryclient.hpp"
#include <qevent.h>
#include "serializer.hpp"

class SchemeWidget : public QWidget
{
    Q_OBJECT
public:
    SchemeWidget(QWidget *parent = nullptr);
    virtual ~SchemeWidget() {};
    BlockWidget* makeWidget(Block *block);
    NetClient netClient;

private:
    std::vector<Block*> blocks;
    QVBoxLayout *vbox;
    void correctNames();

public slots:
    void addBlock(Block*);
    void updateWidgets();
    void run(std::vector<Parameter>* parameters);


protected:
    void paintEvent(QPaintEvent*);
    virtual void dropEvent(QDropEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void schemeChanged();
    void updateSignal(std::vector<Block*> *blocks);
    void resultsRecieved(std::string);
    void errorAppeared(int);
};

#endif // SCHEME_H
