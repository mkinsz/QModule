#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QList>
#include <QObject>
#include <QSharedPointer>

#include "runnable.h"
#include "thread.h"

namespace mkgo {

    class ThreadPool : public QObject
    {
        Q_OBJECT
    public:
        explicit ThreadPool(unsigned threadsCount = QThread::idealThreadCount(), QObject *parent = nullptr);
        virtual ~ThreadPool();

        virtual unsigned threadsCount() const;
        virtual ThreadPool &operator <<(const QSharedPointer<Runnable> &runnable);

    private:

        QList<QSharedPointer<Thread>> _threads;

    };

}

#endif // THREADPOOL_H
