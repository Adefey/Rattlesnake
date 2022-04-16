QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/QTlistofblocks.cpp \
    Sources/Scheme.cpp \
    Sources/UI.cpp \
    Sources/listofblocks.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/qtrequiredvariables.cpp \
    Sources/qtscheme.cpp \
    Sources/splitter.cpp \
    Sources/uiblock.cpp

HEADERS += \
    Headers/Block.h \
    Headers/QTlistofblocks.h \
    Headers/Scheme.h \
    Headers/UI.h \
    Headers/listofblocks.h \
    Headers/mainwindow.h \
    Headers/qtrequiredvariables.h \
    Headers/qtscheme.h \
    Headers/splitter.h \
    Headers/uiblock.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
