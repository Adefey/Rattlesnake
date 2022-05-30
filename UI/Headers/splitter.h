#ifndef SPLITTER_H
#define SPLITTER_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QSplitter>
#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QFile>
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

public slots:
    void open();

private:
    void parseOpenFile(std::string& data, std::string& datascheme, std::string& datareqv);

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
signals:
    void create();
    void save();
    void openscheme(std::string&, std::string&);
};
#endif // SPLITTER_H
