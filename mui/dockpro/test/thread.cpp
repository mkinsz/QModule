#include "thread.h"

#include <QDebug>
#include <QMutexLocker>

#include <iso646.h>

namespace mkgo
{

Thread::Thread(unsigned id, QObject *parent) :
        QObject(parent),
        _id(id),
        _runnablesMutex(QMutex::Recursive)
    {
        moveToThread(&_thread);
        connect(&_thread, &QThread::started, [this]()
        {
            qInfo().noquote() << "Thread" << *this << "has started";
            emit threadStarted();
        });
        connect(&_thread, &QThread::finished, [this]()
        {
            qInfo().noquote() << "Thread" << *this << "has stopped";
            emit threadStopped();
        });
    }

    Thread::~Thread()
    {
        if (not isStarted())
        {
            stop();
        }
    }

    unsigned Thread::id() const
    {
        return _id;
    }

    bool Thread::start()
    {
        bool ok = false;

        if (isStarted())
        {
            qCritical().noquote() << "Thread" << *this << "is already started";
        }
        else
        {
            _thread.start();
            ok = true;
        }

        return ok;
    }

    bool Thread::stop()
    {
        bool ok = false;

        if (!isStarted())
        {
            qCritical().noquote() << "Thread" << *this << "is not running";
        }
        else
        {
            _thread.quit();
            _thread.wait();
            emit threadStopped();
            ok = true;
        }

        return ok;
    }

    bool Thread::isStarted() const
    {
        return _thread.isRunning();
    }

    Thread &Thread::operator <<(const QSharedPointer<Runnable> &runnable)
    {
        if (runnable)
        {
            QMutexLocker lock(&_runnablesMutex);
            for (auto object : runnable->objects())
            {
                if (nullptr != object)
                {
                    object->moveToThread(&_thread);
                }
            }
            _runnables << runnable;
        }
        return *this;
    }

    unsigned Thread::load() const
    {
        unsigned loadsSum = 0;
        QMutexLocker lock(&_runnablesMutex);
        for (const auto &runnable : _runnables)
        {
            if (runnable)
            {
                loadsSum += runnable->load();
            }
        }
        return loadsSum;
    }

}
