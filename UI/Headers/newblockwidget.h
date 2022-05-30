#ifndef NEWBLOCKWIDGET_H
#define NEWBLOCKWIDGET_H

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
#include <string>

#include "block.hpp"

class NewBlockWidget : public QFrame {
    Q_OBJECT
   public:
    explicit NewBlockWidget(QWidget* parent = nullptr, Block block = {});
    virtual ~NewBlockWidget() {}
    Block block;

   protected:
    virtual void mousePressEvent(QMouseEvent* qevent);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);

   private:
    Block* cloneBlock(Block block);

   signals:
    void blockPressed(Block*);
};

#endif  // NEWBLOCKWIDGET_H
