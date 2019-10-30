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

    connect(ui->searchedit, &SearchEdit::search, this, [](QString content) { qDebug() << content; });
    connect(ui->pushButton, &QPushButton::clicked, this, [&] { qDebug() << ui->ipedit->getIpAddress(); });
    connect(ui->msgBtn, &QPushButton::clicked, this, [&] {
        m_nm->notify("消息", "你中大奖啦！", ":/resources/message.png", "https://github.com/mkinsz/qmodule");
    });
}

Components::~Components()
{
    delete ui;
}
