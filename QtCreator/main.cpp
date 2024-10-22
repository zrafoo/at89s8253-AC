#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int x=1920*0.7;
    int y=1080*0.7;
    w.setFixedSize(x,y);
    w.show();
    return a.exec();
}
