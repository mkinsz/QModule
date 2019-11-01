#include "singleapp.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QFileInfo>
#include <QWidget>
#include <QSettings>

SingleApp::SingleApp(int argc,char *argv[]):QApplication(argc,argv)
  ,m_pMainWidget(nullptr), m_localServer(nullptr), m_isRunning(false)
{
    // 取应用程序名作为LocalServer的名字
    m_serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    initLocalConnection();
}

SingleApp::~SingleApp()
{

}

void SingleApp::initLocalConnection()
{
    m_isRunning=false;
    QLocalSocket socket;
    //连接本地服务
    socket.connectToServer(m_serverName);
    if(socket.waitForConnected(500))
    {
        //连接成功
        m_isRunning=true;
        return;
    }
    //连接失败,新建一个
    newLocalServer();
}

void SingleApp::newLocalServer()
{
    m_localServer=new QLocalServer(this);
    connect(m_localServer,&QLocalServer::newConnection,this,&SingleApp::newLocalConnection);
    if(!m_localServer->listen(m_serverName))
    {
        //监听失败，可能是程序崩溃时残留进程服务导致的,移除
        if(m_localServer->serverError() == QAbstractSocket::AddressInUseError)
        {
            QLocalServer::removeServer(m_serverName);
            m_localServer->listen(m_serverName); // 再次监听
        }
    }
}

void SingleApp::newLocalConnection()
{
    QLocalSocket *socket =m_localServer->nextPendingConnection();
    if(socket)
    {
        socket->waitForReadyRead(1000);
        delete socket;
        socket=nullptr;
        activedMainWidget();
    }
}

void SingleApp::activedMainWidget()
{
    if(m_pMainWidget!=Q_NULLPTR)
    {
        QSettings settings("ATUI", "ATMusic");
        m_pMainWidget->restoreGeometry(settings.value("geometry").toByteArray());
        if(m_pMainWidget->windowState()==Qt::WindowMaximized)
            m_pMainWidget->showMaximized();
        else
            m_pMainWidget->show();
        m_pMainWidget->raise();
        m_pMainWidget->activateWindow();
    }
}

bool SingleApp::isRunning()
{
    return m_isRunning;
}
