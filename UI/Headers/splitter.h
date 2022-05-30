#ifndef SPLITTER_H
#define SPLITTER_H

#include <QAction>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QFrame>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include <string>

#include "logwidget.h"
#include "qtlistofblocks.h"
#include "requiredvariables.h"
#include "schemewidget.h"

class Splitter : public QWidget {
    Q_OBJECT

   public:
    explicit Splitter(QWidget* parent = nullptr, QAction* runAction = nullptr);
    virtual ~Splitter() {}

   public slots:
    void open();

   private:
    void parseOpenFile(std::string& data, std::string& datascheme,
                       std::string& datareqv);

   protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
   signals:
    void create();
    void save();
    void openscheme(std::string&, std::string&);
};
#endif  // SPLITTER_H
