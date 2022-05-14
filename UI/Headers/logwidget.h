#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QDebug>

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    LogWidget(QWidget *parent = nullptr);

private:
    QPlainTextEdit *txt;

public slots:
    void sayRequestedBlocks();
//    void sendingScheme();
//    void answer(float);

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
};

#endif // LOGWIDGET_H
