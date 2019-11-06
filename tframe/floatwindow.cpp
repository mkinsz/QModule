#include "floatwindow.h"

#include "mainwindow.h"
#include "cmoveablewindow.h"

FloatWindow::FloatWindow(QWidget *parent) : CMoveableWindow(parent)
{

}

void FloatWindow::initData()
{
    m_width = 200;
}

void FloatWindow::initUI()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::ToolTip);
    setObjectName("CFloatWindow");
}

void FloatWindow::initConnect()
{

}

void FloatWindow::showEvent(QShowEvent *event)
{
    move(MainWindow::getInstance()->x()+ MainWindow::getInstance()->width() + 2,\
         MainWindow::getInstance()->y());
    resize(m_width, MainWindow::getInstance()->height());
    QWidget::showEvent(event);
}

void FloatWindow::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
}

void FloatWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(x() + width(), y());
    CMoveableWindow::mouseMoveEvent(event);
}

