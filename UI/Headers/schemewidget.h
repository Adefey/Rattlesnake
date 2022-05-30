#ifndef SCHEME_H
#define SCHEME_H

#include <qevent.h>
#include <qstring.h>
#include <unistd.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QMetaObject>
#include <QObject>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "appinfo.h"
#include "block.hpp"
#include "blockwidget.h"
#include "netclient.hpp"
#include "netlibraryclient.hpp"
#include "newblockwidget.h"
#include "serializer.hpp"

class SchemeWidget : public QWidget {
    Q_OBJECT
   public:
    SchemeWidget(QWidget* parent = nullptr);
    virtual ~SchemeWidget() {}
    BlockWidget* makeWidget(Block* block);
    NetClient netClient;

   private:
    std::vector<Block*> blocks;
    QVBoxLayout* vbox;
    QWidget* w;
    void correctNames();
    QScrollArea* scrollArea;
    int findCounter(const std::string& str);

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
    virtual void dropEvent(QDropEvent* event);
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dragLeaveEvent(QDragLeaveEvent* event);
    virtual bool eventFilter(QObject* obj, QEvent* event) Q_DECL_OVERRIDE;

   signals:
    void schemeChanged();
    void updateSignal(std::vector<Block*>* blocks);
    void resultsRecieved(std::string);
    void errorAppeared(int);
    void schemeSent();
    void saving(std::string&);
    void openvars(std::string&);
};

#endif  // SCHEME_H
