#include "Scheme.h"
#include "listofblocks.h"
#include <QWidget>
#include "splitter.h"

#ifndef UI_H
#define UI_H

class UI : public QWidget
{
public:
    explicit UI(QWidget *parent = nullptr);
    ~UI();

private:
    void on_drag_and_drop();
    void on_push_run_button();
};

#endif // UI_H
