#ifndef ASTARTE_H 
#define ASTARTE_H 

#define BrushInterface_iid "org.MK.FramewareAndPlugin.UnitInterface"

#include "astarte_global.h"
#include "../../apps/interfaces.h"
#include <QObject>
#include <QWidget>

class ASTARTESHARED_EXPORT Astarte:public QObject,UnitInterface
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID UnitInterface_iid FILE "astarte.json")
   Q_INTERFACES(UnitInterface)

public:
     QString name() const;
     QString iconPath() const;
     QWidget *widget() const;
     UNIT_TYPE unitType() const;
     Qt::DockWidgetArea dockArea() const;
};
#endif // TESTPLUGIN_H
