#include "mgrplugins.h"

#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include <QCoreApplication>

MgrPlugins::MgrPlugins(QObject *parent) : QObject(parent)
{

}

QMap<QString, UnitInterface *> MgrPlugins::plugins()
{
    QDir dir(qApp->applicationDirPath() + "/plugins");

    qDebug() << dir.absolutePath();

    foreach(auto name, dir.entryList(QDir::Files)) {
        qDebug() << dir.absoluteFilePath(name);

        QPluginLoader loader(dir.absoluteFilePath(name));
        QObject *plugin = loader.instance();
        if(plugin) {
            qDebug() << "Load plugin dir: " << name;
            UnitInterface *it = qobject_cast<UnitInterface*>(plugin);
            if(it) {
                m_plugins[it->name()] = it;
            }
        }
    }

    return m_plugins;
}
