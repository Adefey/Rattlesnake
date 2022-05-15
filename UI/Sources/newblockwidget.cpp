#include "newblockwidget.h"

NewBlockWidget::NewBlockWidget(QWidget *parent, Block bl) : QFrame(parent)
{
    block = bl;
    this->setCursor(QCursor(Qt::OpenHandCursor));
}

void NewBlockWidget::mousePressEvent(QMouseEvent *event) {
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
    emit blockPressed(cloneBlock(block));
}

Block* NewBlockWidget::cloneBlock(Block block) {
    std::string solver_path = block.GetSolverPath();
    std::vector<Parameter> given_vars = block.GetGivenVars();
    std::vector<Parameter> solved_vars = block.GetSolvedVars();
    std::string name = block.GetName();
    std::string description = block.GetDescription();
    std::string author_name = block.GetAuthorName();
    int color = block.GetColor();
    Block *new_block = new Block(
        solver_path, given_vars, solved_vars, name, description, author_name, color);
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
