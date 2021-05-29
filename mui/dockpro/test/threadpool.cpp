#include "threadpool.h"

#include <QDebug>
#include <iso646.h>

namespace mkgo {

    ThreadPool::ThreadPool(unsigned threadsCount, QObject *parent) :
        QObject(parent)
    {
        _threads.reserve(threadsCount);
        for (unsigned i = 1; i <= threadsCount; i++)
        {
            _threads.append(QSharedPointer<Thread>(new Thread(i)));
        }
    }

    ThreadPool::~ThreadPool()
    {
    }

    unsigned ThreadPool::threadsCount() const
    {
        return _threads.length();
    }

    ThreadPool &ThreadPool::operator <<(const QSharedPointer<Runnable> &runnable)
    {
        if (_threads.isEmpty())
        {
            qCritical() << "No threads to run with";
        }
        else
        {
            auto lessBusyThread = _threads.first();
            for (const auto &thread : _threads)
            {
                Q_ASSERT(thread);
                if ((thread != lessBusyThread) and (thread->load() < lessBusyThread->load()))
                {
                    lessBusyThread = thread;
                }
            }
            *lessBusyThread << runnable;
        }
        return *this;
    }

}

QDebug operator <<(QDebug debug, const mkgo::Thread &thread)
{
    QDebugStateSaver debugStateSaver(debug);
    debug.noquote().nospace() << "#" << thread.id();
    return debug;
}

