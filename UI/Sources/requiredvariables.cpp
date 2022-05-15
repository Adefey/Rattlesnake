#include "requiredvariables.h"

RequiredVariables::RequiredVariables(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *mainlayout = new QHBoxLayout(parent);
    table = new QTableWidget;
    mainlayout->addWidget(table);
    mainlayout->setAlignment(Qt::AlignCenter);
    table->setColumnCount(2);
    table->setRowCount(5);
    QList<QString> ListOfHeaderLabels = {"Переменная", "Значение"};
    table->setHorizontalHeaderLabels(ListOfHeaderLabels);
    table->adjustSize();
}

void RequiredVariables::updateTable(std::vector<Block*> *blocks) {
    n_rows = 0;
    table->setRowCount(5);
    std::vector<std::string> avaliable_vars;
    for (size_t i = 0; i < blocks->size(); ++i) {
        for (size_t j = 0; j < ((*blocks)[i])->GetGivenVars().size(); ++j) {
            if (n_rows >= 5) {
                table->insertRow(table->rowCount());
            }
            QTableWidgetItem *tableItem1 = new QTableWidgetItem(QString::fromStdString(
                                                                   ((*blocks)[i])->GetName() + "::" + ((*blocks)[i])->GetGivenVars()[j].param_name
                                                                   ));
            tableItem1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            table->setItem(n_rows, 0, tableItem1);
            QComboBox *comboBox = new QComboBox;
            comboBox->setEditable(true);
            for (size_t k = 0; k < i; ++k) {
                for (size_t w = 0; w < ((*blocks)[k])->GetSolvedVars().size(); ++w)
                comboBox->insertItem(comboBox->count(), QString::fromStdString(
                                         ((*blocks)[k])->GetName() + "::" + ((*blocks)[k])->GetSolvedVars()[w].param_name
                                         ));
            }
            table->setCellWidget(n_rows, 1, comboBox);
            ++n_rows;
        }
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
