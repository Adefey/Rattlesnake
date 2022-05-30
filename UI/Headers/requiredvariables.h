#ifndef REQUIREDVARIABLES_H
#define REQUIREDVARIABLES_H

#include <qstring.h>
#include <unistd.h>

#include <QComboBox>
#include <QFile>
#include <QFileDialog>
#include <QHeaderView>
#include <QList>
#include <QMessageBox>
#include <QObject>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <string>
#include <vector>

#include "block.hpp"
#include "parser.hpp"
#include "serializer.hpp"

class RequiredVariables : public QWidget {
    Q_OBJECT
   public:
    explicit RequiredVariables(QWidget* parent = nullptr);
    virtual ~RequiredVariables() {}
    std::vector<Parameter> get_params();

   private:
    size_t n_rows = 0;
    size_t n_rows_answers = 0;
    QTableWidget* table;
    QTableWidget* answers;
    void fixExtension(std::string& filename);
    void parseData(std::string& data, std::string& tableData,
                   std::string& answersData);

   public slots:
    void updateTable(std::vector<Block*>* blocks);
    void updateAnswers(const std::vector<Parameter>& ans);
    void run();
    void clear();
    void save(std::string& dataToSave);
    void open(std::string& data);

   signals:
    void send(std::vector<Parameter>*);
};

#endif  // REQUIREDVARIABLES_H
