#include "systemtray.h"
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QApplication>

SystemTray::SystemTray(QWidget *parent) : QSystemTrayIcon(parent), m_pWidget(parent)
{
    setIcon(QIcon(":/res/music.png"));
    setToolTip(tr("ATUI"));
    QAction *action_show = new QAction(QIcon(":/res/show.png"), QStringLiteral("显示"));
    QAction *action_quit = new QAction(QIcon(":/res/close.png"), QStringLiteral("退出"));
    QMenu *trayMenu = new QMenu();
    trayMenu->addAction(action_show);
    trayMenu->addAction(action_quit);
    setContextMenu(trayMenu);

    connect(action_show, &QAction::triggered, [this] {
        if (m_pWidget->isHidden())
        {
            QSettings settings("ATUI", "AT-MUSIC");
            m_pWidget->restoreGeometry(settings.value("geometry").toByteArray());
            if (m_pWidget->windowState() == Qt::WindowMaximized)
                //时好时坏，目前还不知原因
                m_pWidget->showMaximized();
            else
                m_pWidget->show();
            m_pWidget->raise();
            m_pWidget->activateWindow();
        }
    });
    connect(action_quit, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(this, &QSystemTrayIcon::activated, this, &SystemTray::onActivatedSysTrayIcon);
}

SystemTray::~SystemTray()
{
}

void SystemTray::onActivatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        //单击
        break;
    case QSystemTrayIcon::DoubleClick:
    {
        //双击
        if (m_pWidget->isHidden())
        {
            QSettings settings("ATUI", "AT-MUSIC");
            m_pWidget->restoreGeometry(settings.value("geometry").toByteArray());
            if (m_pWidget->windowState() == Qt::WindowMaximized)
                m_pWidget->showMaximized();
            else
                m_pWidget->show();
            m_pWidget->raise();
            m_pWidget->activateWindow();
        }
        break;
    }
    default:
        break;
    }
}
