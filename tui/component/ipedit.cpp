#include "ipedit.h"

#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

IpEdit::IpEdit(QWidget *parent) : QWidget(parent)
{
    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setSpacing(0);
    m_pLayout->setContentsMargins(0, 0, 0, 0);

    //初始化四个数字输入框
    for (int i = 0; i < 4; ++i)
    {
        m_pSpinBox[i] = new QSpinBox(this);
        m_pSpinBox[i]->setRange(0, 255);
        m_pSpinBox[i]->setButtonSymbols(QAbstractSpinBox::NoButtons);
        m_pSpinBox[i]->setAlignment(Qt::AlignCenter);
        m_pSpinBox[i]->setFixedWidth(40);
        m_pSpinBox[i]->installEventFilter(this);
        m_pLayout->addWidget(m_pSpinBox[i]);

        if (i == 3) continue;

        QLabel *pLabel = new QLabel("·", this);
        pLabel->setFixedWidth(10);
        pLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        pLabel->setFont(QFont("", 15));
        m_pLayout->addWidget(pLabel);
    }

    setLayout(m_pLayout);
}

IpEdit::~IpEdit() {}

QString IpEdit::getIpAddress()
{
    QString ipAddress;
    for (int i = 0; i < 3; i++)
    {
        if (m_pSpinBox[i]->text().isEmpty())
        {
            ipAddress.clear();
            return ipAddress;
        }
        ipAddress += m_pSpinBox[i]->text() + '.';
    }
    ipAddress += m_pSpinBox[3]->text();

    return ipAddress;
}

bool IpEdit::eventFilter(QObject *obj, QEvent *event)
{
    //如果obj不是四个数字输入框，则直接返回
    int nowBox = -1;
    for (int i = 0; i < 4; i++)
    {
        if (obj == m_pSpinBox[i])
            nowBox = i;
    }
    if (-1 == nowBox)
        return false;

    QSpinBox *spinbox = dynamic_cast<QSpinBox *>(obj);
    QKeyEvent *ke = dynamic_cast<QKeyEvent *>(event);

    //如果某个数组输入框获得焦点，则将他们设为全选状态
    if (QEvent::FocusIn == event->type())
    {
        spinbox->selectAll();
        return true;
    }
    //如果输入框中字符为0，则清空该输入框，防止用户多输入0
    else if (QEvent::KeyPress == event->type())
    {
        QString context = spinbox->text();

        if ("0" == context)
            spinbox->clear();

        //如果按下了右键或者点号，则移动到下一格
        if ((ke->key() == Qt::Key_Period) |
            (ke->key() == Qt::Key_Right))
        {
            if ((!m_pSpinBox[nowBox]->text().isEmpty()) && (nowBox < 3))
                m_pSpinBox[nowBox + 1]->setFocus();
        }
        else if (ke->key() == Qt::Key_Left)
        {
            if (nowBox > 0)
                m_pSpinBox[nowBox - 1]->setFocus();
        }
        //如果是删除键，则挨个删除并将焦点移动到第一个数字输入框
        else if (ke->key() == Qt::Key_Backspace)
        {
            if (nowBox > 0)
            {
                m_pSpinBox[nowBox]->setValue(255);
                m_pSpinBox[nowBox - 1]->setFocus();
            }
        }
    }
    //如果输入框内的数字大于25，则输入焦点自动跳到下一格
    else if ((QEvent::KeyRelease == event->type() &&
              (ke->key() != Qt::Key_Backspace)))
    {
        int val = spinbox->value();
        if ((val > 25) && (nowBox < 3))
        {
            m_pSpinBox[nowBox + 1]->setFocus();
        }
    }

    return false;
}

#include "moc_ipedit.cpp"
