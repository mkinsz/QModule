#include "ctoolbutton.h"

#include <QMenu>

CToolButton::CToolButton(QWidget *parent) : QToolButton(parent)
{

}

CToolButton::~CToolButton()
{

}

void CToolButton::setMenu(QMenu *menu)
{
    connect(menu, SIGNAL(aboutToHide()), this, SLOT(onAboutToHide()));
    QToolButton::setMenu(menu);
}

void CToolButton::onAboutToHide()
{

}
