#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QCursor>
#include <QDebug>
#include <QDrag>
#include <QDropEvent>
#include <QFrame>
#include <QMetaObject>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QWidget>
#include <iostream>
#include <string>

#include "block.hpp"

class BlockWidget : public QFrame {
    Q_OBJECT
   public:
    explicit BlockWidget(QWidget* parent = nullptr, Block* block = nullptr);
    virtual ~BlockWidget() = default;
    int pos;

   protected:
    virtual void mousePressEvent(QMouseEvent* qevent);

   private:
    Block* bl;

   signals:
    void blockPressed(Block* bl);
    void blockDeleted(BlockWidget* blockToDelete);
};

#endif  // BLOCKWIDGET_H
