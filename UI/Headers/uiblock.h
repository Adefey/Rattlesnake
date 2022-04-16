#ifndef UIBLOCK_H
#define UIBLOCK_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

class UIBlock : public QWidget {
  Q_OBJECT
public:
  explicit UIBlock(QWidget *parent = nullptr);

signals:
};

#endif // UIBLOCK_H
