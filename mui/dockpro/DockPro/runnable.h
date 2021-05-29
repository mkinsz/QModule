#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QList>

class QObject;

namespace mkgo
{
    class Runnable
    {
    public:
        virtual ~Runnable() { }

        virtual QList<QObject *> objects() = 0;
        virtual unsigned load() const = 0;
    };

}


#endif // RUNNABLE_H
