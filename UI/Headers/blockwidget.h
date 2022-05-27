#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QMouseEvent>
#include <QMetaObject>
#include <QDrag>
#include <QDropEvent>
#include <QCursor>
#include <QMimeData>
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include "block.hpp"
#include <iostream>
#include <string>

#include <QDebug>

class BlockWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BlockWidget(QWidget *parent = nullptr, Block *block = nullptr);
    virtual ~BlockWidget() = default;
    int pos;

protected:
    virtual void mousePressEvent(QMouseEvent *qevent);
    void dropEvent(QDropEvent* event);

private:
    Block *bl;

signals:
    void blockPressed(Block *bl);
    void blockDeleted(BlockWidget* blockToDelete);
};

#endif // BLOCKWIDGET_H
