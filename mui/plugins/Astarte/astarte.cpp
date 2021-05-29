#include "astarte.h" 
#include "form.h"

QString Astarte::name() const
{
    return tr("Astarte");
}

QString Astarte::iconPath() const
{
   return ":/res/astarte.ico";
}

QWidget *Astarte::widget() const
{
    return new Form();
}

UNIT_TYPE Astarte::unitType() const
{
   return UNIT_TYPE::MDIAREA;
}

Qt::DockWidgetArea Astarte::dockArea() const
{
   return Qt::LeftDockWidgetArea;
}
