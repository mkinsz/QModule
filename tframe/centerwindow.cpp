#include "centerwindow.h"
#include <QWidget>

CenterWindow::CenterWindow(QWidget *parent) : CCenterWindow(parent)
{
    QWidget *pWid = new QWidget(this);
    pWid->setStyleSheet("background-color: steelblue");
    addWidget("Home", "Home", pWid);

    pWid = new QWidget(this);
    pWid->setStyleSheet("background-color: lightgray");
    addWidget("Content", "Content", pWid);

    pWid = new QWidget(this);
    pWid->setStyleSheet("background-color: #3D4E57");
    addWidget("About", "About", pWid);

    setAlignment(TopCenter);
}
