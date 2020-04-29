#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setOrganizationName("MK");
    qApp->setOrganizationDomain("https://github.com/mkinsz");
    qApp->setApplicationName("T-Frame");
    qApp->setWindowIcon(QIcon(":/res/logo.ico"));

    MainWindow::window()->show();

    return a.exec();
}
