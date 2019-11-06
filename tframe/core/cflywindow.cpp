#include "cflywindow.h"

#include <QBitmap>
#include <QApplication>
#include <QMouseEvent>
#include <QMenu>
#include <QPainter>

CFlyWindow::CFlyWindow(QWidget *parent) : QWidget(parent)
{
    m_pParent = parent;

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::ToolTip);

    initData();
    initUI();
    initConnect();
}

void CFlyWindow::initData()
{
    m_Pixmap.load(":/res/float.png");
}

void CFlyWindow::initUI()
{
    resize(m_Pixmap.size());
    setMask(m_Pixmap.mask());
}

void CFlyWindow::initConnect()
{

}

void CFlyWindow::setMenu(QMenu *menu)
{
    m_pSettingMenu = menu;
}

void CFlyWindow::mousePressEvent(QMouseEvent *event)
{
    //按住左键可以托动窗口，按下右键关闭程序
    if(event->button() == Qt::LeftButton)
    {
        m_CurrentPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else if(event->button() == Qt::RightButton)
    {
        m_pSettingMenu->exec(QCursor::pos());
    }
}

void CFlyWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_pParent->setVisible(!m_pParent->isVisible());
}

void CFlyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->buttons()) {
        move(event->globalPos() - m_CurrentPos);
        event->accept();
    }
}

void CFlyWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
}

void CFlyWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    //鼠标离开窗口时是普通的指针
    setCursor(Qt::ArrowCursor);
}

void CFlyWindow::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    //鼠标留在窗口上时是一个手指
    setCursor(Qt::PointingHandCursor);
}
