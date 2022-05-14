#include "newblockwidget.h"

NewBlockWidget::NewBlockWidget(QWidget *parent, Block bl) : QFrame(parent)
{
    block = bl;
    qDebug() << bl.color;
    this->setCursor(QCursor(Qt::OpenHandCursor));
}

void NewBlockWidget::mousePressEvent(QMouseEvent *event) {
    qDebug() << block.color;
    if (event->button() != Qt::LeftButton) {
        //event->ignore();
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
    drag->setDragCursor(cursor.pixmap(), Qt::CopyAction);
    painter.end();

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
    qDebug() << block.color;
    emit blockPressed(cloneBlock(block));
}

Block* NewBlockWidget::cloneBlock(Block block) {
    Block *new_block = new Block;
    new_block->solver_path = block.solver_path;
    new_block->given_vars = block.given_vars;
    new_block->solved_vars = block.solved_vars;
    new_block->name = block.name;
    new_block->description = block.description;
    new_block->author_name = block.author_name;
    new_block->color = block.color;
    return new_block;
}

void NewBlockWidget::dragEnterEvent(QDragEnterEvent* event) {
    event->ignore();
}

void NewBlockWidget::dragMoveEvent(QDragMoveEvent* event) {
    event->ignore();
}

void NewBlockWidget::dragLeaveEvent(QDragLeaveEvent* event) {
    event->ignore();
}
