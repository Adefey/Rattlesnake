#ifndef REQUIREDVARIABLES_H
#define REQUIREDVARIABLES_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QList>
#include <qstring.h>
#include <QComboBox>
#include <vector>
#include "block.hpp"

class RequiredVariables : public QWidget
{
    Q_OBJECT
public:
    explicit RequiredVariables(QWidget *parent = nullptr);
    virtual ~RequiredVariables() {};
    std::vector<Parameter> get_params();

private:
    size_t n_rows = 0;
    QTableWidget *table;

public slots:
    void updateTable(std::vector<Block*> *blocks);
    void run();

signals:
    void send(std::vector<Parameter>*);
};

#endif // REQUIREDVARIABLES_H
