#ifndef SAVING_H
#define SAVING_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include"splitter.h"

class SavingWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SavingWidget(QObject *parent = nullptr, QAction *runAction = nullptr);
    virtual ~SavingWidget() {};
};

#endif // SAVING_H