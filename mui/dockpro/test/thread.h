#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QMutex>
#include <QThread>

#include "runnable.h"

namespace mkgo
{
    class Thread : public QObject
    {
        Q_OBJECT
    public:
        explicit Thread(unsigned id = 0, QObject *parent = nullptr);
        virtual ~Thread();

        virtual unsigned id() const;

        virtual bool start();
        virtual bool stop();
        virtual bool isStarted() const;

        virtual Thread &operator <<(const QSharedPointer<Runnable> &runnable);
        virtual unsigned load() const;

    signals:
        void threadStarted();
        void threadStopped();

    private:
        unsigned _id;

        QThread _thread;
        QList<QSharedPointer<Runnable>> _runnables;

        mutable QMutex _runnablesMutex;
    };
}

QDebug operator<< (QDebug debug, const mkgo::Thread &thread);

#endif // THREAD_H
