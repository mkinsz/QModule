#include "mainwindow.h"
#include "singleapp.h"

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    SingleApp a(argc, argv);
    if(!a.isRunning())
    {
        if(!QSystemTrayIcon::isSystemTrayAvailable())
        {
            QMessageBox::critical(nullptr,QObject::tr("Warning"),QObject::tr("No support systemtrayicon"));
            exit(0);
        }

        QFile qss(":/res/style.qss");
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();

        MainWindow w;
        a.m_pMainWidget=&w;
        w.show();

        return a.exec();
    }
    return 0;
}
