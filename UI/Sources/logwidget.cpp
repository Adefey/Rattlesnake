#include "logwidget.h"

LogWidget::LogWidget(QWidget *parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(parent);
    txt = new QPlainTextEdit(this);
    txt->QPlainTextEdit::setReadOnly(true);
    hbox->addWidget(txt);
}

void LogWidget::sayRequestedBlocks() {
    qDebug() << "Log";
    txt->appendPlainText("Отправлен запрос на получение списка блоков...");
}

void LogWidget::answer(std::string result) {
    std::vector<Parameter> results;
    if (!Parser::ParseParametersFromJsonString(result, results)) {
        return;
    }
    txt->appendPlainText("Результаты получены:\n");
    for (size_t i = 0; i < results.size(); ++i) {
        QString name = QString::fromStdString(results[i].param_name);
        QString value = QString::fromStdString(results[i].param_value);
        txt->appendPlainText(name + ": " + value);
    }
}

void LogWidget::errorLog(int cs) {
    switch (cs)
    {
    case 1:
        txt->appendPlainText("Невозможно подключиться к серверу");
        break;
    case 2:
        txt->appendPlainText("Не удалось получить список доступных блоков");
        break;
    case 3:
        txt->appendPlainText("Не удалось отправить схему");
        break;
    case 4:
        txt->appendPlainText("Не удалось получить результат");
        break;
    default:
        break;
    }
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
