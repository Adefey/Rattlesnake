#include "requiredvariables.h"

RequiredVariables::RequiredVariables(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainlayout = new QVBoxLayout(parent);
    table = new QTableWidget;
    mainlayout->addWidget(table);
    mainlayout->setAlignment(Qt::AlignCenter);
    table->setColumnCount(2);
    table->setRowCount(5);
    QList<QString> ListOfHeaderLabels = {"Переменная", "Значение"};
    table->setHorizontalHeaderLabels(ListOfHeaderLabels);
    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    answers = new QTableWidget;
    mainlayout->addWidget(answers);
    answers->setColumnCount(2);
    answers->setRowCount(5);
    answers->setHorizontalHeaderLabels(ListOfHeaderLabels);
    answers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    header = answers->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void RequiredVariables::updateTable(std::vector<Block*> *blocks) {
    n_rows = 0;
    table->setRowCount(5);
    std::vector<std::string> avaliable_vars;
    for (size_t i = 0; i < blocks->size(); ++i) {
        for (size_t j = 0; j < ((*blocks)[i])->given_vars.size(); ++j) {
            if (n_rows >= 5) {
                table->insertRow(table->rowCount());
            }
            QTableWidgetItem *tableItem1 = new QTableWidgetItem(QString::fromStdString(
                                                                   ((*blocks)[i])->name + "::" + ((*blocks)[i])->given_vars[j].param_name
                                                                   ));
            tableItem1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            table->setItem(n_rows, 0, tableItem1);
            QComboBox *comboBox = new QComboBox;
            comboBox->setEditable(true);
            for (size_t k = 0; k < i; ++k) {
                for (size_t w = 0; w < ((*blocks)[k])->solved_vars.size(); ++w)
                comboBox->insertItem(comboBox->count(), QString::fromStdString(
                                         ((*blocks)[k])->name + "::" + ((*blocks)[k])->solved_vars[w].param_name
                                         ));
            }
            table->setCellWidget(n_rows, 1, comboBox);
            ++n_rows;
        }
    }
}

void RequiredVariables::updateAnswers(const std::vector<Parameter> &ans) {
    n_rows_answers = 0;
    answers->setRowCount(5);
    for (size_t i = 0; i < ans.size(); ++i) {
        if (n_rows_answers >= 5) {
            answers->insertRow(answers->rowCount());
        }
        QTableWidgetItem *tableItem1 = new QTableWidgetItem(QString::fromStdString(ans[i].param_name));
        QTableWidgetItem *tableItem2 = new QTableWidgetItem(QString::fromStdString(ans[i].param_value));
        answers->setItem(n_rows_answers, 0, tableItem1);
        answers->setItem(n_rows_answers, 1, tableItem2);
        ++n_rows_answers;
    }
}

void RequiredVariables::run() {
    std::vector<std::string> names;
    for (size_t i = 0; i < n_rows; ++i) {
        QTableWidgetItem *item = table->item(i, 0);
        if (item != NULL) {
            names.push_back(item->text().toStdString());
        }
    }
    std::vector<std::string> values;
    for (size_t i = 0; i < n_rows; ++i) {
        values.push_back(qobject_cast<QComboBox*>(table->cellWidget(i, 1))->currentText().toStdString());
    }
    std::vector<Parameter> parameters;
    for (size_t i = 0; i < names.size(); ++i) {
        Parameter parameter(names[i], values[i]);
        parameters.push_back(parameter);
    }
    emit send(&parameters);
}
