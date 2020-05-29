#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class WsClient : public QObject
{
    Q_OBJECT
public:
    explicit WsClient(const QUrl &url, QObject *parent = nullptr);
    ~WsClient();

    void send(const QString &msg);
    void send(const QByteArray &a);

    void open(const QUrl &url);
    void close();

Q_SIGNALS:
    void connected();
    void disconnected();
    void recv(const QString &msg);

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onRecvText(const QString &msg);
    void onRecvBin(const QByteArray &msg);

private:
    QWebSocket m_ws;
    QUrl m_url;
};

#endif // WSCLIENT_H
