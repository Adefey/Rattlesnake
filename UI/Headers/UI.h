#ifndef UI_H
#define UI_H

#include <QObject>
#include <QWidget>
#include "splitter.h"

class UI : public QWidget
{
    Q_OBJECT
public:
    explicit UI(QObject *parent = nullptr, QAction *runAction = nullptr);
    virtual ~UI() {};

signals:
    void create();
    void save();
    void open();
};

#endif // UI_H
