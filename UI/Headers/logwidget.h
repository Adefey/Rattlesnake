#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <string>
#include <vector>
#include <block.hpp>
#include <parser.hpp>

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    LogWidget(QWidget *parent = nullptr);
    virtual ~LogWidget() {};

private:
    QPlainTextEdit *txt;

public slots:
    void sayRequestedBlocks();
//    void sendingScheme();
    void answer(std::string result);
    void errorLog(int cs);

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
};

#endif // LOGWIDGET_H
