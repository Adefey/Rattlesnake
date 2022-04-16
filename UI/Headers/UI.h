#include "Scheme.h"
#include "listofblocks.h"
#include "splitter.h"
#include <QWidget>
#include "netclient.hpp"
#include "netlibraryclient.hpp"

#ifndef UI_H
#define UI_H

class UI : public QWidget {
public:
  explicit UI(QWidget *parent = nullptr);
  ~UI();
  bool on_start();

private:
  void on_drag_and_drop();
  void on_push_run_button();
};

#endif // UI_H
