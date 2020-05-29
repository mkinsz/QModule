#include "downloadmanager.h"

#include "httpdownloader.h"

#include <QtMath>
#include <QMetaEnum>
#include <QSettings>
#include <QDesktopServices>
#include <QMessageBox>

DownloadManager::DownloadManager(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    dlview->setShowGrid(false);
    dlview->verticalHeader()->hide();
    dlview->horizontalHeader()->hide();
    dlview->setAlternatingRowColors(true);
    dlview->horizontalHeader()->setStretchLastSection(true);

    cleanbtn->setIcon(QIcon(":/res/delete.png"));
    setbtn->setIcon(QIcon(":/res/settings.png"));

    m_model = new DownloadModel(this);
    dlview->setModel(m_model);
    connect(cleanbtn, SIGNAL(clicked()), this, SLOT(cleanup()));
    // load();
}

DownloadManager::~DownloadManager()
{

}

void DownloadManager::download(const QUrl &url)
{
    if(!isVisible()) show();
    DownloadItem *m = new DownloadItem(url, this);
    connect(m, &DownloadItem::itemDelete, this, &DownloadManager::delItem);
    addItem(m);
}

void DownloadManager::addItem(DownloadItem *item)
{
    int row = m_downloads.count();
    m_model->beginInsertRows(QModelIndex(), row, row);
    m_downloads.append(item);
    m_model->endInsertRows();
    // TODO: update item counts
    dlview->setIndexWidget(m_model->index(row, 0), item);
    dlview->setRowHeight(row, item->sizeHint().height());
}

void DownloadManager::cleanup()
{
    if (m_downloads.isEmpty()) return;
    m_model->removeRows(0, m_downloads.count());
}

void DownloadManager::load()
{
    QSettings settings;
    settings.beginGroup(QLatin1String("downloadmanager"));
    QSize size = settings.value(QLatin1String("size")).toSize();
    if (size.isValid())
        resize(size);
    QByteArray value = settings.value(QLatin1String("removeDownloadsPolicy"), QLatin1String("Never")).toByteArray();
    //    QMetaEnum removePolicyEnum = staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("RemovePolicy"));
    //    m_removePolicy = removePolicyEnum.keyToValue(value) == -1 ?
    //                Never :
    //                static_cast<RemovePolicy>(removePolicyEnum.keyToValue(value));

    int i = 0;
    QString key = QString(QLatin1String("download_%1_")).arg(i);
    while (settings.contains(key + QLatin1String("url"))) {
        QUrl url = settings.value(key + QLatin1String("url")).toUrl();
        QString fileName = settings.value(key + QLatin1String("location")).toString();
        bool done = settings.value(key + QLatin1String("done"), true).toBool();
        if (done && !url.isEmpty() && !fileName.isEmpty()) {
            DownloadItem *m = new DownloadItem(this);
            m->m_file.setFile(fileName);
            m->filelb->setText(m->m_file.fileName());
            m->m_url = url;
            m->probar->hide();
            addItem(m);
        }
        key = QString(QLatin1String("download_%1_")).arg(++i);
    }
    //    cleanbtn->setEnabled(m_downloads.count() - activeDownloads() > 0);
}

void DownloadManager::save() const
{
    QSettings settings;
    settings.beginGroup(QLatin1String("downloadmanager"));
    //    QMetaEnum removePolicyEnum = staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("RemovePolicy"));
    //    settings.setValue(QLatin1String("removeDownloadsPolicy"), QLatin1String(removePolicyEnum.valueToKey(m_removePolicy)));
    settings.setValue(QLatin1String("size"), size());

    for (int i = 0; i < m_downloads.count(); ++i) {
        QString key = QString(QLatin1String("download_%1_")).arg(i);
        settings.setValue(key + QLatin1String("url"), m_downloads[i]->m_url);
        settings.setValue(key + QLatin1String("location"), m_downloads[i]->m_file.filePath());
        settings.setValue(key + QLatin1String("done"), m_downloads[i]->downloadSuccess());
    }
    int i = m_downloads.count();
    QString key = QString(QLatin1String("download_%1_")).arg(i);
    while (settings.contains(key + QLatin1String("url"))) {
        settings.remove(key + QLatin1String("url"));
        settings.remove(key + QLatin1String("location"));
        settings.remove(key + QLatin1String("done"));
        key = QString(QLatin1String("download_%1_")).arg(++i);
    }
}

void DownloadManager::delItem()
{
    DownloadItem* m = qobject_cast<DownloadItem*>(sender());
    if (!m) return;
    if(m_downloads.contains(m)) {
        int i = m_downloads.indexOf(m);
        if(i >= 0)
            m_model->removeRows(i, 1);
    }
}

DownloadItem::DownloadItem(QWidget *parent):
    QWidget(parent)
{
    setupUi(this);
    m_pDownloader = new HttpDownloader(this);

    connect(m_pDownloader, &HttpDownloader::error, this, &DownloadItem::error);
    connect(m_pDownloader, &HttpDownloader::readyWrite, this, &DownloadItem::readyWrite);
    connect(m_pDownloader, &HttpDownloader::finished, this, &DownloadItem::finished);
}

DownloadItem::DownloadItem(const QUrl &url, QWidget *parent):
    QWidget(parent), m_url(url), m_bytesRecved(0)
{
    setupUi(this);
    probar->setValue(0);
    delbtn->setIcon(QIcon(":/res/close.png"));
    opbtn->setIcon(QIcon(":/res/play.png"));

    m_pDownloader = new HttpDownloader(this);
    m_pDownloader->stUrl(url);

    QString szUrl = url.toString();
    int index = szUrl.lastIndexOf("/");
    if (index >= 0) {
        QString name = szUrl.right(szUrl.length() - index - 1);
        QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/" + name;
        filelb->setText(path);
        m_pDownloader->setDestPath(path);
        qDebug() << "Download File: " << szUrl << name << path;
    }

    m_timer.setInterval(10);
    connect(&m_timer, &QTimer::timeout, this, &DownloadItem::timeout);
    connect(m_pDownloader, &HttpDownloader::error, this, &DownloadItem::error);
    connect(m_pDownloader, &HttpDownloader::readyWrite, this, &DownloadItem::readyWrite);
    connect(m_pDownloader, &HttpDownloader::finished, this, &DownloadItem::finished);
    connect(opbtn, SIGNAL(clicked()), this, SLOT(operate()));
    connect(delbtn, SIGNAL(clicked()), this, SIGNAL(itemDelete()));
}

bool DownloadItem::downloading() const
{
    return HttpDownloader::t_Downloading == m_pDownloader->getCurrentStatus();
}

bool DownloadItem::downloadSuccess() const
{
    return HttpDownloader::t_Finished == m_pDownloader->getCurrentStatus();
}

void DownloadItem::operate()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (m_pDownloader->getCurrentStatus() == HttpDownloader::t_Finished) {
        QFileInfo info(filelb->text());
        QDesktopServices::openUrl(QUrl(info.absolutePath()));
    }
    else if (m_pDownloader->getCurrentStatus() != HttpDownloader::t_Downloading) {
        btn->setIcon(QIcon(":/res/pause.png"));
        m_pDownloader->start();
        m_timer.start();
    } else {
        btn->setIcon(QIcon(":/res/play.png"));
        m_pDownloader->pause();
        m_timer.stop();
    }
}

void DownloadItem::readyWrite()
{
    int currentSize = 0, totalSize = 0;
    m_pDownloader->getProgress(currentSize, totalSize);
    dllb->setText(QString::number(qCeil(currentSize/1024)) + "KB / " + QString::number(qCeil(totalSize/1024)) + "KB");
}

void DownloadItem::finished()
{
    int currentSize = 0, totalSize = 0;
    m_pDownloader->getProgress(currentSize, totalSize);
    QString str = tr("Download Finished, Size: ") + QString::number(qCeil(totalSize/1024)) + "KB";
    dllb->setText(str);
    probar->setValue(100);
    opbtn->setIcon(QIcon(":/res/folder.png"));
}

void DownloadItem::timeout()
{
    if (m_pDownloader->getCurrentStatus() != HttpDownloader::t_Downloading) return;

    int currentSize = 0, totalSize = 0;
    m_pDownloader->getProgress(currentSize, totalSize);
    dllb->setText(QString::number(qCeil(currentSize/1024)) + "KB / " + QString::number(qCeil(totalSize/1024)) + "KB");
    if (totalSize > 0)
        probar->setValue(qCeil(currentSize*1.0/totalSize*100));
}

void DownloadItem::error(const QString &error)
{
    qDebug() << "Error: " << error;
}

DownloadModel::DownloadModel(DownloadManager *downloadManager, QObject *parent)
    : QAbstractListModel(parent)
    , m_downMg(downloadManager) {

}

QVariant DownloadModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount(index.parent()))
        return QVariant();
    if (role == Qt::ToolTipRole)
        if (!m_downMg->m_downloads.at(index.row())->downloadSuccess())
            return m_downMg->m_downloads.at(index.row())->dllb->text();
    return QVariant();
}

int DownloadModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid()) ? 0 : m_downMg->m_downloads.count();
}

bool DownloadModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid()) return false;

    if(1 == count) {
        if (!m_downMg->m_downloads.at(row)->downloadSuccess()) {
            int ret = QMessageBox::question(nullptr, "提示", "任务未结束，是否确认删除?", "确认", "取消");
            if(ret) return false;
        }
        beginRemoveRows(parent, row, row);
        m_downMg->m_downloads.takeAt(row)->deleteLater();
        endRemoveRows();
        return true;
    }

    int lastRow = row + count - 1;
    for (int i = lastRow; i >= row; --i) {
        if (m_downMg->m_downloads.at(i)->downloadSuccess()) {
            beginRemoveRows(parent, i, i);
            m_downMg->m_downloads.takeAt(i)->deleteLater();
            endRemoveRows();
        }
    }
    return true;
}
