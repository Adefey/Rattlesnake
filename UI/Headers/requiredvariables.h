#ifndef REQUIREDVARIABLES_H
#define REQUIREDVARIABLES_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QList>
#include <qstring.h>
#include <QComboBox>
#include <vector>
#include <block.h>
#include <schemewidget.h>

class RequiredVariables : public QWidget
{
    Q_OBJECT
public:
    explicit RequiredVariables(QWidget *parent = nullptr);

private:
    size_t n_rows = 0;
    QTableWidget *table;

public slots:
    void updateTable(std::vector<Block*> *blocks);

signals:

};

#endif // REQUIREDVARIABLES_H
