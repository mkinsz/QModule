#ifndef TST_RUNNABLE_H
#define TST_RUNNABLE_H

#include <gmock/gmock.h>
#include <QList>

#include "../dockpro/runnable.h"

class QObject;

namespace mkgo {
    class RunnableMock : public Runnable
    {
    public:
        virtual ~RunnableMock() {}

        MOCK_METHOD0(run, void());
        MOCK_METHOD0(objects, QList<QObject*>());
        MOCK_CONST_METHOD0(load, unsigned());
    };
}

#endif // TST_RUNNABLE_H
