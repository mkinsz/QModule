#include "cnavigationbar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>

CNavigationBar::CNavigationBar(QWidget *parent) : QFrame(parent)
{
    initData();
    initUI();
    initConnect();
}

void CNavigationBar::initData()
{
    m_index = 0;
}

void CNavigationBar::initUI()
{
    setObjectName("CNavigationBar");
}

void CNavigationBar::initConnect()
{
    for(auto item : m_buttons)
        connect(item, SIGNAL(clicked()), this, SLOT(setButtonChecked()));
}

void CNavigationBar::addNavigationTile(const QString &tile, const QString &objectName)
{
    QPushButton* button = new QPushButton(tile);
    button->setFlat(true);
    button->setCheckable(true);
    button->setFixedSize(80, 60);
    button->setFocusPolicy(Qt::NoFocus);
    m_buttons.append(button);
    button->setObjectName(objectName);
    connect(button, SIGNAL(clicked()), this, SLOT(setButtonChecked()));
}

void CNavigationBar::setAlignTopLeft()
{
    if(!m_topLeft)
        m_topLeft = new QHBoxLayout(this);
    for(auto item : m_buttons)
        m_topLeft->addWidget(item);

    m_topLeft->addStretch();
    m_topLeft->setMargin(0);
    m_topLeft->setSpacing(0);
    setLayout(m_topLeft);
}

void CNavigationBar::setAlignTopCenter()
{
    if(!m_topCenter)
        m_topCenter = new QHBoxLayout(this);
    m_topCenter->addStretch();
    for(auto item : m_buttons)
        m_topCenter->addWidget(item);

    m_topCenter->addStretch();
    m_topCenter->setMargin(0);
    m_topCenter->setSpacing(0);
    setLayout(m_topCenter);
}

void CNavigationBar::setAlignTopRight()
{
    if(!m_topRight)
        m_topRight = new QHBoxLayout(this);
    m_topRight->addStretch();
    for(auto item : m_buttons)
        m_topRight->addWidget(item);

    m_topRight->setMargin(0);
    m_topRight->setSpacing(0);
    setLayout(m_topRight);
}


void CNavigationBar::setAlignBottomLeft()
{
    if(!m_bottomLeft)
        m_bottomLeft = new QHBoxLayout;
    for(auto item : m_buttons)
        m_bottomLeft->addWidget(item);

    m_bottomLeft->addStretch();
    m_bottomLeft->setMargin(0);
    m_bottomLeft->setSpacing(0);
    setLayout(m_bottomLeft);
}


void CNavigationBar::setAlignBottomCenter()
{
    if(!m_bottomCenter)
        m_bottomCenter = new QHBoxLayout;
    m_bottomCenter->addStretch();
    for(auto item : m_buttons)
        m_bottomCenter->addWidget(item);

    m_bottomCenter->addStretch();
    m_bottomCenter->setMargin(0);
    m_bottomCenter->setSpacing(0);
    setLayout(m_bottomCenter);
}

void CNavigationBar::setAlignBottomRight()
{
    if(!m_bottomRight)
        m_bottomRight = new QHBoxLayout(this);
    m_bottomRight->addStretch();
    for(auto item : m_buttons)
        m_bottomRight->addWidget(item);

    m_bottomRight->setMargin(0);
    m_bottomRight->setSpacing(0);
    setLayout(m_bottomRight);
}

void CNavigationBar::setAlignLeftTop()
{
    if(!m_leftTop)
        m_leftTop = new QVBoxLayout(this);
    for(auto item : m_buttons)
        m_leftTop->addWidget(item);

    m_leftTop->addStretch();
    m_leftTop->setMargin(0);
    m_leftTop->setSpacing(0);
    setLayout(m_leftTop);
}

void CNavigationBar::setAlignLeftCenter()
{
    if(!m_leftCenter)
        m_leftCenter = new QVBoxLayout(this);
    m_leftCenter->addStretch();
    for(auto item : m_buttons)
        m_leftCenter->addWidget(item);

    m_leftCenter->addStretch();
    m_leftCenter->setMargin(0);
    m_leftCenter->setSpacing(0);
    setLayout(m_leftCenter);
}

void CNavigationBar::setAlignLeftBottom()
{
    if(!m_leftBottom)
        m_leftBottom = new QVBoxLayout(this);
    m_leftBottom->addStretch();
    for(auto item : m_buttons)
        m_leftBottom->addWidget(item);

    m_leftBottom->setMargin(0);
    m_leftBottom->setSpacing(0);
    setLayout(m_leftBottom);
}

void CNavigationBar::setAlignRightTop()
{
    if(!m_rightTop)
        m_rightTop = new QVBoxLayout(this);
    for(auto item : m_buttons)
        m_rightTop->addWidget(item);

    m_rightTop->addStretch();
    m_rightTop->setMargin(0);
    m_rightTop->setSpacing(0);
    setLayout(m_rightTop);
}

void CNavigationBar::setAlignRightCenter()
{
    if(!m_rightCenter)
        m_rightCenter = new QVBoxLayout(this);
    m_rightCenter->addStretch();
    for(auto item : m_buttons)
        m_rightCenter->addWidget(item);

    m_rightCenter->addStretch();
    m_rightCenter->setMargin(0);
    m_rightCenter->setSpacing(0);
    setLayout(m_rightCenter);
}

void CNavigationBar::setAlignRightBottom()
{
    m_rightBottom = new QVBoxLayout;
    m_rightBottom->addStretch();
    for(auto item : m_buttons)
        m_rightBottom->addWidget(item);

    m_rightBottom->setMargin(0);
    m_rightBottom->setSpacing(0);
    setLayout(m_rightBottom);
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

