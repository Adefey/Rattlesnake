#pragma once

#ifndef SPLITTER_H
#define SPLITTER_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QFrame>
#include <QSplitter>
#include <QTlistofblocks.h>

class Splitter : public QWidget
{
    Q_OBJECT

public:
    explicit Splitter(QWidget *parent = nullptr);
    ~Splitter();
signals:

};
#endif // SPLITTER_H
