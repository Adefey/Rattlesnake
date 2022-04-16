#pragma once

#ifndef SPLITTER_H
#define SPLITTER_H

#include <QFrame>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSplitter>
#include <QTlistofblocks.h>

class Splitter : public QWidget {
  Q_OBJECT

public:
  explicit Splitter(QWidget *parent = nullptr);
  ~Splitter();
signals:
};
#endif // SPLITTER_H
