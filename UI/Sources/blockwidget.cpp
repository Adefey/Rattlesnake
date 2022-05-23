#include "blockwidget.h"

BlockWidget::BlockWidget(QWidget *parent, Block *block) : QFrame(parent)
{
    bl = block;
    this->setCursor(QCursor(Qt::OpenHandCursor));
    QSizePolicy sp_retain = this->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    this->setSizePolicy(sp_retain);
}

void BlockWidget::mousePressEvent(QMouseEvent *event) {
    // if (event->button() == Qt::RightButton) {
    //     std::cout << "OK";
    //     emit blockDeleted(bl->name_);
    //     return;
    // }
    if (event->button() != Qt::LeftButton) {
        event->ignore();
        return;
    }
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    QPainter painter(this);
    QPixmap pixmap(this->size());
    this->render(&pixmap);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    QPoint point = event->pos();
    drag->setHotSpot(point);
    QCursor cursor(Qt::ClosedHandCursor);
    drag->setDragCursor(cursor.pixmap(), Qt::MoveAction);
    painter.end();
    this->setVisible(false);
    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
    this->setVisible(true);
}

void BlockWidget::dropEvent(QDropEvent* event)
{
//  if(event->source() == this && event->possibleActions() & Qt::MoveAction)
}

