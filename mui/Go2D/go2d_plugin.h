#ifndef GO2D_PLUGIN_H
#define GO2D_PLUGIN_H

#include <QQmlExtensionPlugin>

class Go2dPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // GO2D_PLUGIN_H
