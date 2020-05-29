#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include "ui_downloads.h"
#include "ui_downloaditem.h"

#include <QUrl>
#include <QDialog>
#include <QFileInfo>
#include <QTableView>
#include <QTimer>

class DownloadItem;
class DownloadModel;
class HttpDownloader;

class DownloadManager : public QDialog, public Ui_Downloads
{
    Q_OBJECT
public:
    explicit DownloadManager(QWidget *parent = nullptr);
    ~DownloadManager();

    void download(const QUrl &url);

private:
    void addItem(DownloadItem *item);

private Q_SLOTS:
    void cleanup();
    void load();
    void save() const;
    void delItem();

public : Q_SIGNALS:


private:
    friend class DownloadModel;

    DownloadModel *m_model;
    QList<DownloadItem*> m_downloads;
};

class DownloadItem : public QWidget, public Ui_DownloadItem
{
    Q_OBJECT

public:
    explicit DownloadItem(QWidget *parent=nullptr);
    explicit DownloadItem(const QUrl &url, QWidget *parent = nullptr);

    bool downloading() const;
    bool downloadSuccess() const;

private Q_SLOTS:
    void operate();
    void readyWrite();
    void finished();
    void timeout();

    void error(const QString &error);

public : Q_SIGNALS:
    void itemDelete();

private:
    friend class DownloadManager;

    QUrl m_url;
    QFileInfo m_file;
    QTimer m_timer;

    qint64 m_bytesRecved;

    HttpDownloader* m_pDownloader = nullptr;
};

class DownloadModel : public QAbstractListModel
{
    friend class DownloadManager;
    Q_OBJECT

public:
    DownloadModel(DownloadManager *downloadManager, QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    DownloadManager *m_downMg;
};

#endif // DOWNLOADMANAGER_H
