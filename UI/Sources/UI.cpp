#include "UI.h"

UI::UI(QObject *parent) {
    QGridLayout *mainlayout = new QGridLayout(this);
    Splitter *splitter = new Splitter(this);
    mainlayout->addWidget(splitter);
}

