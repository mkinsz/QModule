#include "cmoveablewindow.h"
#include <QMouseEvent>

CMoveableWindow::CMoveableWindow(QWidget *parent) : QFrame(parent)
{

}

void CMoveableWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        m_dragPos = e->globalPos() - frameGeometry().topLeft();
        m_bPressed = true;
    }
    e->accept();
}


void CMoveableWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    e->accept();
}

void CMoveableWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(e->globalPos() - m_dragPos);
    }
    e->accept();
}
