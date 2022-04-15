#ifndef UIBLOCK_H
#define UIBLOCK_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>

class UIBlock : public QWidget
{
    Q_OBJECT
public:
    explicit UIBlock(QWidget *parent = nullptr);

signals:

};

#endif // UIBLOCK_H
