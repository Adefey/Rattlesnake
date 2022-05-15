#ifndef NEWBLOCKWIDGET_H
#define NEWBLOCKWIDGET_H

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
#include <string>
#include "block.hpp"

#include <QDebug>

class NewBlockWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NewBlockWidget(QWidget *parent = nullptr, Block block = {});
    virtual ~NewBlockWidget() {};
    Block block;

protected:
    virtual void mousePressEvent(QMouseEvent *qevent);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);

private:
    Block* cloneBlock(Block block);

signals:
    void blockPressed(Block*);
};

#endif // NEWBLOCKWIDGET_H
