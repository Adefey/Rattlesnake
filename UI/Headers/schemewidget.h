#ifndef SCHEME_H
#define SCHEME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <qstring.h>
#include <QLabel>
#include <vector>
#include <map>
#include <set>
#include <QDebug>
#include <QMetaObject>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMessageBox>
#include <QCoreApplication>
#include <iostream>
#include "block.hpp"
#include "blockwidget.h"
#include "newblockwidget.h"
#include "netclient.hpp"
#include "netlibraryclient.hpp"
#include <qevent.h>
#include <unistd.h>
#include "serializer.hpp"
#include "appinfo.h"

class SchemeWidget : public QWidget
{
    Q_OBJECT
public:
    SchemeWidget(QWidget *parent = nullptr);
    virtual ~SchemeWidget() {};
    BlockWidget* makeWidget(Block *block);
    NetClient netClient;

private:
    std::vector<Block*> blocks;
    QVBoxLayout *vbox;
    QWidget *w;
    void correctNames();
    QScrollArea *scrollArea;
    int findCounter(const std::string str);

public slots:
    void addBlock(Block*);
    void deleteBlock(BlockWidget*);
    void updateWidgets();
    void run(std::vector<Parameter>* parameters);
    void clear();
    void save();
    void open(std::string& data, std::string& vars);

protected:
    void paintEvent(QPaintEvent*);
    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

signals:
    void schemeChanged();
    void updateSignal(std::vector<Block*> *blocks);
    void resultsRecieved(std::string);
    void errorAppeared(int);
    void schemeSent();
    void saving(std::string&);
    void openvars(std::string&);
};

#endif // SCHEME_H
