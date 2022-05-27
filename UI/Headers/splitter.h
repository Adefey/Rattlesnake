#ifndef SPLITTER_H
#define SPLITTER_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QSplitter>
#include <QAction>
#include <QApplication>
#include "qtlistofblocks.h"
#include "schemewidget.h"
#include "logwidget.h"
#include "requiredvariables.h"

class Splitter : public QWidget
{
    Q_OBJECT

public:
    explicit Splitter(QWidget *parent = nullptr, QAction *runAction = nullptr);
    virtual ~Splitter() {};

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
signals:
    
};
#endif // SPLITTER_H
