#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QApplication::setStyle("Fusion");
    a.setStyle("Fusion");
    a.setFont(QFont("Microsoft Yahei", 12));

    MainWindow w;
    w.show();

    return a.exec();
}
