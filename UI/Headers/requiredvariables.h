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
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <vector>
#include "block.hpp"
#include "serializer.hpp"
#include "parser.hpp"
#include <unistd.h>
#include <iostream>

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
    void fixExtension(std::string& filename);
    void parseData(std::string& data, std::string& tableData, std::string& answersData);

public slots:
    void updateTable(std::vector<Block*> *blocks);
    void updateAnswers(const std::vector<Parameter> &ans);
    void run();
    void clear();
    void save(std::string& dataToSave);
    void open(std::string& data);

signals:
    void send(std::vector<Parameter>*);
};

#endif // REQUIREDVARIABLES_H
