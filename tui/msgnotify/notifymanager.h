#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QObject>
#include <QQueue>

#include "notifybox.h"

class NotifyManager : public QObject
{
    Q_OBJECT
public:
    explicit NotifyManager(QObject *parent = nullptr);

    void notify(const QString &title, const QString &body,
                const QString &icon, const QString url);
    void setMaxCount(int count);
    void setDisplayTime(int ms);

private:
    class NotifyData
    {
    public:
        NotifyData(const QString &icon, const QString &title,
                   const QString &body, const QString url) : icon(icon),
                                                             title(title),
                                                             body(body),
                                                             url(url)
        {
        }

        QString icon;
        QString title;
        QString body;
        QString url;
    };

    void rearrange();
    void showNext();

    QQueue<NotifyData> dataQueue;
    QList<NotifyBox *> notifyList;
    int maxCount;
    int displayTime;
};

#endif // NOTIFYMANAGER_H
