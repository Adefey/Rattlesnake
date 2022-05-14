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
#include "block.h"
#include "blockwidget.h"
#include "newblockwidget.h"
#include <qevent.h>

class SchemeWidget : public QWidget
{
    Q_OBJECT
public:
    SchemeWidget(QWidget *parent = nullptr);
    BlockWidget* makeWidget(Block *block);

private:
    std::vector<Block*> blocks;
    QVBoxLayout *vbox;
    void correctNames();

public slots:
    void addBlock(Block*);
    void updateWidgets();


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
};

#endif // SCHEME_H
