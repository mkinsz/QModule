#include "components.h"
#include "ui_components.h"

#include "notifymanager.h"

#include <QDebug>

Components::Components(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::Components),
                                          m_nm(new NotifyManager(this))
{
    ui->setupUi(this);

    setFocusPolicy(Qt::ClickFocus);

    ui->titleBar->addItem("推荐");
    ui->titleBar->addItem("电台");
    ui->titleBar->addItem("排行");
    ui->titleBar->addItem("歌单");
    ui->titleBar->addItem("搜索");
    ui->titleBar->setBarColor(QColor(255, 255, 255));
    ui->titleBar->setItemColor(QColor(209, 216, 240));
    ui->titleBar->setTextColor(QColor(58, 58, 58));
    ui->titleBar->setLineWidth(3);
    ui->titleBar->setLineColor(QColor(133, 153, 216));
    ui->titleBar->setLineStyle(SiderBar::ItemBottom);
    ui->titleBar->moveTo(0);

    connect(ui->searchEdit, &SearchEdit::search, this, [](QString content) { qDebug() << content; });
    connect(ui->pushButton, &QPushButton::clicked, this, [&] { qDebug() << ui->ipEdit->getIpAddress(); });
    connect(ui->msgBtn, &QPushButton::clicked, this, [&] {
        m_nm->notify("消息", "你中大奖啦！", ":/resources/message.png", "https://github.com/mkinsz/qmodule");
    });
}

Components::~Components()
{
    delete ui;
}
