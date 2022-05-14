#include "logwidget.h"

LogWidget::LogWidget(QWidget *parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(parent);
    txt = new QPlainTextEdit(this);
    txt->QPlainTextEdit::setReadOnly(true);
    txt->appendPlainText("Отправлен запрос на получение списка блоков...");
    hbox->addWidget(txt);
}

void LogWidget::sayRequestedBlocks() {
    qDebug() << "Log";
    txt->appendPlainText("Отправлен запрос на получение списка блоков...");
}

void LogWidget::dragEnterEvent(QDragEnterEvent* event) {
    event->ignore();
}

void LogWidget::dragMoveEvent(QDragMoveEvent* event) {
    event->ignore();
}

void LogWidget::dragLeaveEvent(QDragLeaveEvent* event) {
    event->ignore();
}
