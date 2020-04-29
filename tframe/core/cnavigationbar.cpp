#include "cnavigationbar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>

CNavigationBar::CNavigationBar(QWidget *parent) : QFrame(parent)
{
    initData();
    initUi();
    initEvt();
}

void CNavigationBar::initData()
{
    m_index = 0;
}

void CNavigationBar::initUi()
{
    setObjectName("CNavigationBar");
}

void CNavigationBar::initEvt()
{

}

void CNavigationBar::addNavigationTile(const QString &tile, const QString &objectName)
{
    m_names << tile;
    QPushButton* button = new QPushButton(tile);
    button->setFlat(true);
    button->setCheckable(true);
    button->setFixedSize(80, 60);
    button->setFocusPolicy(Qt::NoFocus);
    button->setObjectName(objectName);
    m_buttons.append(button);
    connect(button, SIGNAL(clicked()), this, SLOT(setButtonChecked()));
}

void CNavigationBar::setVAlign(CCenterWindow::EDIR_ALIGNMENT direct)
{
    m_vLayout = new QVBoxLayout(this);
    m_vLayout->setMargin(0);
    m_vLayout->setSpacing(0);
    setLayout(m_vLayout);

    switch (direct) {
    case CCenterWindow::LeftTop:
    case CCenterWindow::RightTop:
        for(auto item : m_buttons)
            m_vLayout->addWidget(item);
        m_vLayout->addStretch();
        break;

    case CCenterWindow::LeftCenter:
    case CCenterWindow::RightCenter:
        m_vLayout->addStretch();
        for(auto item : m_buttons)
            m_vLayout->addWidget(item);
        m_vLayout->addStretch();
        break;

    case CCenterWindow::LeftBottom:
    case CCenterWindow::RightBottom:
        m_vLayout->addStretch();
        for(auto item : m_buttons)
            m_vLayout->addWidget(item);
        break;
    default:;
    }
}

void CNavigationBar::setHAlign(CCenterWindow::EDIR_ALIGNMENT direct)
{
    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setMargin(0);
    m_hLayout->setSpacing(0);
    setLayout(m_hLayout);

    switch (direct) {
    case CCenterWindow::TopLeft:
    case CCenterWindow::BottomRight:
        for(auto item : m_buttons)
            m_hLayout->addWidget(item);
        m_hLayout->addStretch();
        break;

    case CCenterWindow::TopCenter:
    case CCenterWindow::BottomCenter:
        m_hLayout->addStretch();
        for(auto item : m_buttons)
            m_hLayout->addWidget(item);
        m_hLayout->addStretch();
        break;

    case CCenterWindow::TopRight:
    case CCenterWindow::BottomLeft:
        m_hLayout->addStretch();
        for(auto item : m_buttons)
            m_hLayout->addWidget(item);
        break;
    default:;
    }
}

int CNavigationBar::currentIndex()
{
    return m_index;
}

void CNavigationBar::setCurrentIndex(int index)
{
    m_buttons.at(index)->click();
}

int CNavigationBar::count()
{
    return m_buttons.size();
}

void CNavigationBar::setButtonChecked()
{
    for (int i = 0; i < m_buttons.size(); ++i) {
        if (m_buttons.at(i) == sender())
        {
            m_buttons.at(i)->setChecked(true);
            emit indexChanged(i);
            m_index = i;
        }
        else{
            m_buttons.at(i)->setChecked(false);
        }
    }
}

