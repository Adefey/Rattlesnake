#include "UI.h"

UI::UI(QObject *parent, QAction *runAction) {
    QGridLayout *mainlayout = new QGridLayout(this);
    Splitter *splitter = new Splitter(this, runAction);
    mainlayout->addWidget(splitter);
}

