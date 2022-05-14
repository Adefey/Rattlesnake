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
    qDebug() << "update Table";
    n_rows = 0;
    table->setRowCount(5);
    std::vector<std::string> avaliable_vars;
    for (size_t i = 0; i < blocks->size(); ++i) {
        for (size_t j = 0; j < ((*blocks)[i])->given_vars.size(); ++j) {
            if (n_rows >= 5) {
                table->insertRow(table->rowCount());
            }
            QTableWidgetItem *tableItem1 = new QTableWidgetItem(QString::fromStdString(
                                                                   ((*blocks)[i])->name + "::" + ((*blocks)[i])->given_vars[j].var_name
                                                                   ));
            tableItem1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            table->setItem(n_rows, 0, tableItem1);
            QComboBox *comboBox = new QComboBox;
            for (size_t k = 0; k < i; ++k) {
                for (size_t w = 0; w < ((*blocks)[k])->solved_vars.size(); ++w)
                comboBox->insertItem(comboBox->count(), QString::fromStdString(
                                         ((*blocks)[k])->name + "::" + ((*blocks)[k])->solved_vars[w].var_name
                                         ));
            }
            table->setCellWidget(n_rows, 1, comboBox);
            ++n_rows;
        }
    }
}
