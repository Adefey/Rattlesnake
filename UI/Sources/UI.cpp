#include "UI.h"

UI::UI(QObject *parent, QAction *runAction) {
    QGridLayout *mainlayout = new QGridLayout(this);
    Splitter *splitter = new Splitter(this, runAction);
    QObject::connect(this, SIGNAL(create()), splitter, SIGNAL(create()));
    mainlayout->addWidget(splitter);
}

