#include "floatwindow.h"

#include "mainwindow.h"
#include "cmoveablewindow.h"

FloatWindow::FloatWindow(QWidget *parent) : CMoveableWindow(parent)
{
    initData();
    initUi();
    initEvt();
}

void FloatWindow::initData()
{
    m_width = 200;
}

void FloatWindow::initUi()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::ToolTip);
    setObjectName("FloatWindow");
    hide();
}

void FloatWindow::initEvt()
{

}

void FloatWindow::showEvent(QShowEvent *event)
{
    move(MainWindow::window()->x()+ MainWindow::window()->width() + 2,\
         MainWindow::window()->y());
    resize(m_width, MainWindow::window()->height());
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

