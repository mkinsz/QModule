#include "ccenterwindow.h"
#include "cnavigationbar.h"
#include "ctitlebar.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QStackedWidget>

CCenterWindow::CCenterWindow(QWidget *parent) : QWidget(parent)
{
    initData();
    initUI();
    initConnect();
}

void CCenterWindow::initData()
{
    m_preIndex = 0;
}

void CCenterWindow::initUI()
{
    setObjectName("CCenterWindow");
    m_pNavigation = new CNavigationBar(this);
    m_pStacked = new QStackedWidget(this);

    m_pLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    m_pLayout->addWidget(m_pNavigation);
    m_pLayout->addWidget(m_pStacked);
    m_pLayout->setContentsMargins(8, 0 , 8, 8);
    m_pLayout->setSpacing(0);

    setLayout(m_pLayout);
}

void CCenterWindow::swicthLayout(QBoxLayout::Direction direction)
{
    m_pLayout->setDirection(direction);
}

void CCenterWindow::setAlignment(EDIR_ALIGNMENT direction)
{
    switch (direction) {
    case TopLeft:
        m_pNavigation->setObjectName(QString("nav_bottom"));
        m_pNavigation->setAlignTopLeft();
        m_pNavigation->resize(QSize(m_pStacked->width(), m_pNavigation->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::TopToBottom);
        break;
    case TopCenter:
        m_pNavigation->setObjectName(QString("nav_bottom"));
        m_pNavigation->setAlignTopCenter();
        m_pNavigation->resize(QSize(m_pStacked->width(), m_pNavigation->height()));
        m_pNavigation->adjustSize();

        swicthLayout(QBoxLayout::TopToBottom);
        break;
    case TopRight:
        m_pNavigation->setObjectName(QString("nav_bottom"));
        m_pNavigation->setAlignTopRight();
        m_pNavigation->resize(QSize(m_pStacked->width(), m_pNavigation->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::TopToBottom);
        break;
    case RightTop:
        m_pNavigation->setObjectName(QString("nav_left"));
        m_pNavigation->setAlignRightTop();
        m_pNavigation->resize(QSize(m_pNavigation->width(), m_pStacked->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::RightToLeft);
        break;
    case RightCenter:
        m_pNavigation->setObjectName(QString("nav_left"));
        m_pNavigation->setAlignRightCenter();
        m_pNavigation->resize(QSize(m_pNavigation->width(), m_pStacked->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::RightToLeft);
        break;
    case RightBottom:
        m_pNavigation->setObjectName(QString("nav_left"));
        m_pNavigation->setAlignRightBottom();
        m_pNavigation->resize(QSize(m_pNavigation->width(), m_pStacked->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::RightToLeft);
        break;
    case BottomRight:
        m_pNavigation->setObjectName(QString("nav_top"));
        m_pNavigation->setAlignBottomRight();
        m_pNavigation->resize(QSize(m_pStacked->width(), m_pNavigation->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::BottomToTop);
        break;
    case BottomCenter:
        m_pNavigation->setObjectName(QString("nav_top"));
        m_pNavigation->setAlignBottomCenter();
        m_pNavigation->resize(QSize(m_pStacked->width(), m_pNavigation->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::BottomToTop);
        break;
    case BottomLeft:
        m_pNavigation->setObjectName(QString("nav_top"));
        m_pNavigation->setAlignBottomLeft();
        m_pNavigation->resize(QSize(m_pStacked->width(), m_pNavigation->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::BottomToTop);
        break;
    case LeftBottom:
        m_pNavigation->setObjectName(QString("nav_right"));
        m_pNavigation->setAlignLeftBottom();
        m_pNavigation->resize(QSize(m_pNavigation->width(), m_pStacked->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::LeftToRight);
        break;
    case LeftCenter:
        m_pNavigation->setObjectName(QString("nav_right"));
        m_pNavigation->setAlignLeftCenter();
        m_pNavigation->resize(QSize(m_pNavigation->width(), m_pStacked->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::LeftToRight);
        break;
    case LeftTop:
        m_pNavigation->setObjectName(QString("nav_right"));
        m_pNavigation->setAlignLeftTop();
        m_pNavigation->resize(QSize(m_pNavigation->width(), m_pStacked->height()));
        m_pNavigation->adjustSize();
        swicthLayout(QBoxLayout::LeftToRight);
        break;
    }
}

void CCenterWindow::initConnect()
{
    connect(m_pNavigation, SIGNAL(indexChanged(int)), this, SLOT(switchscreen(int)));
}

void CCenterWindow::addWidget(const QString &tile, const QString &obejctName, QWidget *widget)
{
    m_pNavigation->addNavigationTile(tile, obejctName);
    widget->setObjectName(obejctName);
    m_pStacked->addWidget(widget);
}

CNavigationBar* CCenterWindow::getNavigationBar(){
    return m_pNavigation;
}

void CCenterWindow::switchscreen(const int index)
{
    int n = 0;
    if (index == m_pStacked->currentIndex())
    {
        return;
    }
    else if(index > m_pStacked->currentIndex())
    {
        n = 2;
    }
    else if (index < m_pStacked->currentIndex())
    {
        n = 6;
    }

    m_pStacked->setCurrentIndex(index);

    switch (n) {
    case 0:
        cloudAntimation(AnimationTop);
        break;
    case 1:
        cloudAntimation(AnimationTopRight);
        break;
    case 2:
        cloudAntimation(AnimationRight);
        break;
    case 3:
        cloudAntimation(AnimationBottomRight);
        break;
    case 4:
        cloudAntimation(AnimationBottom);
        break;
    case 5:
        cloudAntimation(AnimationBottomLeft);
        break;
    case 6:
        cloudAntimation(AnimationLeft);
        break;
    case 7:
        cloudAntimation(AnimationTopLeft);
        break;
    case 8:
        cloudAntimation(AnimationCenter);
        break;
    default:
        break;
    }
    m_preIndex = index;

}

void CCenterWindow::switchscreen()
{
    m_pStacked->setCurrentIndex(m_curIndex);
}

void CCenterWindow::cloudAntimation(EDIR_ANIMATION direction)
{
    QLabel* circle = new QLabel(m_pStacked->currentWidget());
    QLabel* line = new QLabel(this);
    line->setObjectName(QString("AntimationLine"));
    line->resize(0, 2);
    line->show();
    circle->setPixmap(m_pStacked->widget(m_preIndex)->grab());

    circle->show();
    circle->resize(m_pStacked->currentWidget()->size());
    QPropertyAnimation *animation = new QPropertyAnimation(circle, "geometry");

    animation->setDuration(1000);
    animation->setStartValue(circle->geometry());

    QPropertyAnimation* animation_line = new QPropertyAnimation(line, "size");
    animation_line->setDuration(1000);
    animation_line->setEasingCurve(QEasingCurve::OutCubic);

    switch (direction) {
    case AnimationTop:
        animation->setEndValue(QRect(circle->x(), circle->y() - 10, circle->width(), 0));
        break;
    case AnimationTopRight:
        animation->setEndValue(QRect(circle->width(), 0, 0, 0));
        break;
    case AnimationRight:
        line->move(0, m_pStacked->y() - 2);
        animation->setEndValue(QRect(circle->width() + 3, 0, 0, circle->height()));
        animation_line->setStartValue(QSize(0, 2));
        animation_line->setEndValue(QSize(m_pStacked->width(), 2));
        break;
    case AnimationBottomRight:
        animation->setEndValue(QRect(circle->width(), circle->height(), 0, 0));
        break;
    case AnimationBottom:
        animation->setEndValue(QRect(0, circle->height() + 10, circle->width(), 0));
        break;
    case AnimationBottomLeft:
        animation->setEndValue(QRect(0, circle->height(), 0, 0));
        break;
    case AnimationLeft:
        animation->setEndValue(QRect(-3, 0, 0, circle->height()));
        line->move(m_pStacked->x(), m_pStacked->y() - 2);
        animation_line->setStartValue(QSize(0, 2));
        animation_line->setEndValue(QSize(m_pStacked->width(), 2));
        break;
    case AnimationTopLeft:
        animation->setEndValue(QRect(0, 0, 0, 0));
        break;
    case AnimationCenter:
        animation->setEndValue(QRect(circle->width()/2, circle->height()/2, 0, 0));
        break;
    }
    animation->setEasingCurve(QEasingCurve::OutCubic);

    QPropertyAnimation* animation_opacity = new QPropertyAnimation(circle, "windowOpacity");
    animation_opacity->setDuration(1000);
    animation_opacity->setStartValue(1);
    animation_opacity->setEndValue(0);
    animation_opacity->setEasingCurve(QEasingCurve::OutCubic);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    connect(group,SIGNAL(finished()), circle, SLOT(hide()));
    connect(group,SIGNAL(finished()), circle, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), line, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), group, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation_opacity, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation_line, SLOT(deleteLater()));
    group->addAnimation(animation);
    group->addAnimation(animation_opacity);
    group->addAnimation(animation_line);
    group->start();
}
