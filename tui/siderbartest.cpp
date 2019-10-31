#pragma execution_character_set("utf-8")
#include "siderbartest.h"
#include "ui_siderbartest.h"

SiderBarTest::SiderBarTest(QWidget *parent) : QWidget(parent),
                                              ui(new Ui::SiderBarTest)
{
    ui->setupUi(this);

    ui->widget->setOrientation(Qt::Vertical);
    ui->widget->addItem("主界面");
    ui->widget->addItem("系统设置");
    ui->widget->addItem("防区管理");
    ui->widget->addItem("警情查询");
    ui->widget->addItem("视频预览");

    connect(ui->widget, SIGNAL(itemClicked(int, QString)), this, SLOT(updateLabel(int, QString)));
}

SiderBarTest::~SiderBarTest()
{
    delete ui;
}

void SiderBarTest::updateLabel(int index, QString str)
{
    Q_UNUSED(index)
    ui->label->setText(QString("%1").arg(str));
}
