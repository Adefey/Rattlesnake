#ifndef REQUIREDVARIABLES_H
#define REQUIREDVARIABLES_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QList>
#include <qstring.h>
#include <QComboBox>
#include <QHeaderView>
#include <vector>
#include "block.hpp"
#include <unistd.h>

class RequiredVariables : public QWidget
{
    Q_OBJECT
public:
    explicit RequiredVariables(QWidget *parent = nullptr);
    virtual ~RequiredVariables() {};
    std::vector<Parameter> get_params();

private:
    size_t n_rows = 0;
    size_t n_rows_answers = 0;
    QTableWidget *table;
    QTableWidget *answers;

public slots:
    void updateTable(std::vector<Block*> *blocks);
    void updateAnswers(const std::vector<Parameter> &ans);
    void run();

signals:
    void send(std::vector<Parameter>*);
};

#endif // REQUIREDVARIABLES_H
