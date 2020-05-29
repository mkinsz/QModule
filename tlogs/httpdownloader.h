#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

#include <QObject>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
class QFile;
class QNetworkAccessManager;
QT_END_NAMESPACE

class HttpDownloader : public QObject
{
    Q_OBJECT

public:
    enum DownloadStatus
    {
        t_Start,                // 起始状态
        t_Downloading,          // 下载中
        t_Pause,                // 暂停
        t_Finished,             // 下载完成
        t_Error                 // 错误
    };

public:
    HttpDownloader(QObject* parent = nullptr);
    ~HttpDownloader();

    void stUrl(const QUrl& url);
    void start();
    void pause();
    void setDestPath(const QString& fileName);
    void getProgress(int& currentSize, int& totalSize);
    DownloadStatus getCurrentStatus(void);

private slots:
    void replyFinished(QNetworkReply* reply);
    void readyRead();
    void errored(QNetworkReply::NetworkError);

private:
    void requestFile();

signals:
    void error(const QString& errored);
    void readyWrite();
    void finished();

private:
    int m_totalSize = 0;    //文件大小
    int m_size = 0;         //已下载大小
    int m_limit = 524288;    //限速下载

    QUrl m_url;
    QFile* m_file = nullptr;
    DownloadStatus m_status = t_Start;
    QNetworkAccessManager* m_pNetworkManager = nullptr;
};

#endif // HTTPDOWNLOADER_H
