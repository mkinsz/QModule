#ifndef SINGLEAPP_H
#define SINGLEAPP_H

#include <QApplication>

class QLocalServer;
class QWidget;

class SingleApp : public QApplication
{
    Q_OBJECT
public:
    explicit SingleApp(int argc,char *argv[]);
    ~SingleApp();

    bool isRunning();       //判断进程是否存在

public:
    QWidget *m_pMainWidget; //主窗口

private slots:
    void newLocalConnection();

private:
    //初始化本地连接
    void initLocalConnection();
    //新建服务端
    void newLocalServer();
    //激活已存在的窗口
    void activedMainWidget();

private:
    QLocalServer *m_localServer;

    QString m_serverName;

    bool m_isRunning;
};

#endif // SINGLEAPP_H
