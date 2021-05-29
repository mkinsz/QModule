#ifndef MGRPLUGINS_H
#define MGRPLUGINS_H

#include <QMap>
#include <QObject>

#include "interfaces.h"

class MgrPlugins : public QObject
{
    Q_OBJECT
public:
    explicit MgrPlugins(QObject *parent = nullptr);

    QMap<QString, UnitInterface*> plugins();

private:
    QMap<QString, UnitInterface*> m_plugins;

signals:

};

#endif // MGRPLUGINS_H
