#include "titlebar.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyle>
#include <QEvent>
#include <QMouseEvent>
#include <QLineEdit>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setObjectName("global_tb");
    setFixedHeight(50);
    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);
    m_pMiniButton = new QPushButton(this);

    //搜索框
    //    m_pSearchLineEdit=new QLineEdit(this);

    //设置按钮样式
    //    m_pCloseButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarCloseButton));
    //    m_pMaximizeButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarMaxButton));
    //    m_pMinimizeButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarMinButton));

    m_pMiniButton->setStyleSheet("border-image: url(:/res/mini.svg)");
    m_pCloseButton->setStyleSheet("border-image: url(:/res/close.svg)");
    m_pMinimizeButton->setStyleSheet("border-image: url(:/res/minimize.svg)");

    m_pCloseButton->setFlat(true);
    m_pMaximizeButton->setFlat(true);
    m_pMinimizeButton->setFlat(true);
    m_pMiniButton->setFlat(true);

    m_pIconLabel->setObjectName("tb_icon_label");
    m_pTitleLabel->setObjectName("tb_title_label");
    m_pMaximizeButton->setObjectName("tb_max_button");
    m_pMinimizeButton->setObjectName("tb_min_button");
    m_pCloseButton->setObjectName("tb_close_button");
    m_pMiniButton->setObjectName("tb_mini_button");

    m_pCloseButton->setToolTip(QStringLiteral("关闭"));
    m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
    m_pMinimizeButton->setToolTip(QStringLiteral("最小化"));

    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);
    m_pTitleLabel->setFixedWidth(200);

    m_pMinimizeButton->setFixedSize(20, 20);
    m_pMaximizeButton->setFixedSize(20, 20);
    m_pCloseButton->setFixedSize(20, 20);
    m_pMiniButton->setFixedSize(20, 20);

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addSpacing(20);
    //pLayout->addWidget(m_pSearchLineEdit);
    pLayout->addStretch(0);
    pLayout->addSpacing(200);
    pLayout->addWidget(m_pMiniButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);

    setLayout(pLayout);

    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

TitleBar::~TitleBar()
{
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit m_pMaximizeButton->clicked();
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    break;
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    break;
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    default:;
    }

    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(QStringLiteral("还原"));
            m_pMaximizeButton->setStyleSheet("#tb_max_button { border-image: url(:/res/normal.svg); }");
            //            QPixmap pix=style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
            //            m_pMaximizeButton->setIcon(pix);
        }
        else
        {
            m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
            m_pMaximizeButton->setStyleSheet("#tb_max_button { border-image: url(:/res/maximize.svg); }");
            //            QPixmap pix=style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
            //            m_pMaximizeButton->setIcon(pix);
        }
    }
}
