#include "mainframe.h"
#include "helps/helps.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto app = Helps::App::instance();
    app->loadInfo();

    MainFrame m;
    Helps::App::setStyle(":/res/qss/black.css");
    m.show();

    return a.exec();
}
