#include "httpdownloader.h"

#include <QSslSocket>
#include <QNetworkProxy>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QDataStream>
#include <QFile>
#include <QDebug>

HttpDownloader::HttpDownloader(QObject* parent)
    :QObject(parent)
{
    m_pNetworkManager = new QNetworkAccessManager(this);
    connect(m_pNetworkManager, &QNetworkAccessManager::finished, \
            this, &HttpDownloader::replyFinished);

//    QNetworkProxy proxy;
//    proxy.setType(QNetworkProxy::HttpProxy);
//    proxy.setHostName("127.0.0.1");
//    proxy.setPort(8888);
//    m_pNetworkManager->setProxy(proxy);
}

HttpDownloader::~HttpDownloader()
{
    delete m_file;
}

void HttpDownloader::replyFinished(QNetworkReply* reply)
{
    if (m_status == t_Start) {
        QString lengthString = reply->rawHeader("Content-Length");
        if (lengthString.isEmpty()) {
            emit error(tr("Get File Size Failed..."));
            return;
        }

        m_totalSize = lengthString.toInt();  //设置文件大小

        qDebug() << "Recv Finished: " << "Current Size is "  << m_size << "; Total Size is " << m_totalSize;

        emit readyWrite();
        return;
    } else {
        if (m_totalSize <= m_size) {
            m_file->close();    // 接收完成
            m_status = t_Finished;
            emit finished();
            return;
        }
        requestFile();  // 继续发送
    }

    reply->deleteLater();
}

void HttpDownloader::requestFile()
{
    if (m_size >= m_totalSize || m_status != t_Downloading) return;

    QNetworkRequest networkRequest;
    networkRequest.setUrl(m_url);
    networkRequest.setRawHeader("User-Agent", "Msp-HttpDownLoader");
    networkRequest.setRawHeader("Accept", "application/octet-stream");

    QString range = "bytes=%1-%2"; // 设置获取文件的范围
    int rangeRValue = m_size + m_limit;
    if (rangeRValue > m_totalSize)
        rangeRValue = m_totalSize;
    range = range.arg(m_size).arg(m_size + m_limit);
    networkRequest.setRawHeader("Range", range.toUtf8());

    QNetworkReply *reply = m_pNetworkManager->get(networkRequest); // 发送请求
    connect(reply, &QNetworkReply::readyRead, this, &HttpDownloader::readyRead);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(errored(QNetworkReply::NetworkError)));
}

void HttpDownloader::readyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    QByteArray byteArray = reply->readAll();
    if (byteArray.size() <= 0) {
        m_status = t_Error;
        emit error(tr("Recv File Data Failed..."));
        return;
    }

    m_size += byteArray.size();
    m_file->write(byteArray);
    m_file->flush();
}

void HttpDownloader::errored(QNetworkReply::NetworkError errorcode)
{
    emit error(tr("Recv Data Error:") + QString::number(errorcode));
}

void HttpDownloader::stUrl(const QUrl &url)
{
    m_url = url;
    m_totalSize = 0;
    m_size = 0;

    QNetworkRequest networkRequest;
    networkRequest.setUrl(url);
    networkRequest.setRawHeader("User-Agent", "Msp-HttpDownLoader");
    networkRequest.setRawHeader("Accept", "application/octet-stream");
    m_pNetworkManager->head(networkRequest); // head请求（获取文件大小）
}

void HttpDownloader::setDestPath(const QString& fileName)
{
    if (m_file != nullptr) delete m_file;

    m_file = new QFile(fileName);
    m_file->open(QFile::WriteOnly);
}

void HttpDownloader::getProgress(int& currentSize, int& totalSize)
{
    currentSize = m_size;
    totalSize = m_totalSize;
}

void HttpDownloader::start()
{
    if (m_status != t_Start && m_status != t_Pause) return;

    m_status = t_Downloading;
    requestFile();
}

void HttpDownloader::pause()
{
    m_status = t_Pause;
}

HttpDownloader::DownloadStatus HttpDownloader::getCurrentStatus(void)
{
    return m_status;
}
