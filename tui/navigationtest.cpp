#include "navigationtest.h"
#include "ui_navigationtest.h"

NavigationTest::NavigationTest(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::NavigationTest)
{
    ui->setupUi(this);

    initForm();
}

NavigationTest::~NavigationTest()
{
    delete ui;
}

void NavigationTest::initForm()
{
    ui->listView1->setIcoColorBg(false);
    ui->listView1->setColorLine(QColor(255, 255, 255));
    ui->listView1->setColorBg(QColor(238, 238, 238), QColor(255, 69, 0), QColor(255, 160, 122));
    ui->listView1->setColorText(QColor(10, 10, 10), QColor(254, 255, 239), QColor(10, 10, 10));

    ui->listView2->setIcoColorBg(false);
    ui->listView2->setColorLine(QColor(193, 193, 193));
    ui->listView2->setColorBg(QColor(255, 255, 255), QColor(232, 236, 245), QColor(242, 242, 242));
    ui->listView2->setColorText(QColor(19, 36, 62), QColor(19, 36, 62), QColor(19, 36, 62));

    ui->listView3->setIcoColorBg(false);
    ui->listView3->setColorLine(QColor(32, 53, 74));
    ui->listView3->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
    ui->listView3->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));

    ui->listView1->setInfoVisible(false);
    ui->listView2->setInfoVisible(false);
    ui->listView3->setInfoVisible(false);

    ui->listView3->setLineVisible(false);
    ui->listView3->setIcoStyle(Navigation::IcoStyle_Triangle);

    ui->listView1->readData(":/navigation/config.xml");
    ui->listView2->readData(":/navigation/config.xml");
    ui->listView3->readData(":/navigation/config.xml");
}
