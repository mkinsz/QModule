#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QString>
#include <QMainWindow>
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QStandardItemModel;
QT_END_NAMESPACE

class WsClient;
class DownloadManager;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUI();
    static DownloadManager *downloadManager();

protected:
    void timerEvent(QTimerEvent *);

private Q_SLOTS:
    void recv(const QString &msg);
    void send(const QString &evt, const QJsonObject &obj=QJsonObject());
    void connected();
    void handleClick();
    void handleSearch(const QString &text);
    void handleDelete();

private:
    void query(const bool download = false);
    void handleTokenAck(const QJsonObject &json);
    void handleLoginAck(const QJsonObject &json);
    void handleAliveAck(const QJsonObject &json);
    void handleLogQueryAck(const QJsonObject &json);
    void handleLogExportAck(const QJsonObject &json);

    typedef void (MainWindow::*handler)(const QJsonObject &json);

private:
    Ui::MainWindow *ui;
    WsClient *m_ws;
    int m_tid;

    uint m_ndt = 0;   //现在时间戳
    uint m_pdt = 0;   //过去
    uint m_size = 17; //大小
    uint m_offset = 0;//偏移

    QString m_cd;
    QString m_tk;

    QStandardItemModel *m_model;
    QMap<QString, handler> m_mapFun;

    static DownloadManager *s_downMg;
};
#endif // MAINWINDOW_H
