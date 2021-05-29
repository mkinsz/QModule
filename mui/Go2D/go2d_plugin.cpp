#include "go2d_plugin.h"

#include "go2d.h"

#include <qqml.h>

void Go2dPlugin::registerTypes(const char *uri)
{
    // @uri Go2D
    qmlRegisterType<Go2D>(uri, 1, 0, "Go2D");
}

