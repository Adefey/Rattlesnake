#include <mainwindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QApplication::desktop();
    //w.resize(4200, 2800);
    w.setWindowTitle("Rattlesnake");
    w.showMaximized();
    return a.exec();
}
