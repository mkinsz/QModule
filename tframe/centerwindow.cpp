#include "centerwindow.h"
#include <QWidget>

CenterWindow::CenterWindow(QWidget *parent) : CCenterWindow(parent)
{
    QWidget *pWid = new QWidget(this);
    pWid->setStyleSheet("background-color: #666666");
    addWidget("主页", "Home", pWid);

    pWid = new QWidget(this);
    pWid->setStyleSheet("background-color: #3D4E57");
    addWidget("内容", "Content", pWid);

    pWid = new QWidget(this);
    pWid->setStyleSheet("background-color: #6A6A6A");
    addWidget("关于", "About", pWid);

    setAlignment(TopLeft);
}
