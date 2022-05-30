#include "UI.h"

UI::UI(QObject* parent, QAction* runAction) {
    QGridLayout* mainlayout = new QGridLayout(this);
    Splitter* splitter = new Splitter(this, runAction);
    QObject::connect(this, SIGNAL(create()), splitter, SIGNAL(create()));
    QObject::connect(this, SIGNAL(save()), splitter, SIGNAL(save()));
    QObject::connect(this, SIGNAL(open()), splitter, SLOT(open()));
    mainlayout->addWidget(splitter);
}
