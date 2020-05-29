#include "wsclient.h"
#include <QDebug>
#include <QAbstractSocket>

WsClient::WsClient(const QUrl &url, QObject *parent) : QObject(parent), m_url(url)
{
    connect(&m_ws, &QWebSocket::connected, this, &WsClient::onConnected, Qt::UniqueConnection);
    connect(&m_ws, &QWebSocket::disconnected, this, &WsClient::onDisconnected, Qt::UniqueConnection);
    m_ws.open(QUrl(url));
}

WsClient::~WsClient()
{
    m_ws.close();
}

void WsClient::send(const QString &msg)
{
    if(QAbstractSocket::ConnectedState != m_ws.state()) return;

    m_ws.sendTextMessage(msg);
}

void WsClient::send(const QByteArray &a)
{
    if(QAbstractSocket::ConnectedState != m_ws.state()) return;

    m_ws.sendBinaryMessage(a);
}

void WsClient::open(const QUrl &url)
{
    connect(&m_ws, &QWebSocket::connected, this, &WsClient::onConnected, Qt::UniqueConnection);
    connect(&m_ws, &QWebSocket::disconnected, this, &WsClient::onDisconnected, Qt::UniqueConnection);
    m_ws.open(QUrl(url));
}

void WsClient::close()
{
    qDebug() << "Current State:" << m_ws.state();
    m_ws.close();
}

void WsClient::onConnected()
{
    connect(&m_ws, &QWebSocket::textMessageReceived, this, &WsClient::onRecvText);
    connect(&m_ws, &QWebSocket::binaryMessageReceived, this, &WsClient::onRecvBin);
//    connect(&m_ws, &QWebSocket::textMessageReceived, this, [] { qDebug() << "Recv data..."; });

    qDebug() << "ws connected...";
    emit connected();
}

void WsClient::onDisconnected()
{
    qDebug() << "ws disconnected...";
    emit disconnected();
}

void WsClient::onRecvText(const QString &msg)
{
    qDebug() << "Text received:" << msg;
    emit recv(msg);
}

void WsClient::onRecvBin(const QByteArray &msg)
{
//    qDebug() << "Binary received:" << msg.constData();
    emit recv(msg);
}
