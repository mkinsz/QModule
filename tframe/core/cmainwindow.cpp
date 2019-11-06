#include "cmainwindow.h"

#include "cflywindow.h"
#include "ctitlebar.h"
#include "ccenterwindow.h"
#include "ctoolbutton.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QScreen>
#include <QSettings>
#include <QPropertyAnimation>
#include <QStatusBar>
#include <QSystemTrayIcon>


CMainWindow::CMainWindow(QWidget *parent)
    : QWidget(parent)
{
    initData();
    initUI();
    initConnect();
}

void CMainWindow::initData()
{
    m_bPressed = false;
    m_bLockMoved = false;
    m_bLocked = false;
}

void CMainWindow::initUI()
{
    setObjectName(QString("CMainWindow"));
    QScreen* pScreen = qApp->primaryScreen();
    setMaximumSize(pScreen->availableGeometry().size());
    readSettings();

    m_pLayout = new QVBoxLayout(this);
    m_pTitleBar = new CTitleBar(this);
    m_pLayout->addWidget(m_pTitleBar);

    m_pLayout->setMargin(0);
    m_pLayout->setSpacing(0);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("QFramer");

    m_pTrayIcon = new QSystemTrayIcon(QIcon(":/res/logo.ico"), this);
    m_pTrayIcon->setObjectName("trayicon");
    m_pTrayIcon->setToolTip(QString(qApp->applicationName()));
    m_pTrayIcon->show();

    m_pFlyWin = new CFlyWindow(this);
    m_pFlyWin->move(pScreen->availableGeometry().width() / 5 * 4, pScreen->availableGeometry().height() / 5);
}


void CMainWindow::initConnect( )
{
    connect(m_pTitleBar, SIGNAL(minimuned()), this, SIGNAL(Hidden()));
    connect(m_pTitleBar, SIGNAL(closed()), this, SIGNAL(Hidden()));
    connect(m_pTitleBar, SIGNAL(minimuned()), this, SLOT(hide()));
    connect(m_pTitleBar, SIGNAL(minimuned()), this, SLOT(showFlyWindow()));
    connect(m_pTitleBar, SIGNAL(maximumed()), this, SLOT(swithMaxNormal()));
    connect(m_pTitleBar, SIGNAL(closed()), this, SLOT(hide()));
    connect(m_pTitleBar, SIGNAL(closed()), this, SLOT(showFlyWindow()));
    connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
}

QWidget *CMainWindow::centralWidget()
{
    return m_pCentral;
}

void CMainWindow::setCentralWidget(QWidget *widget)
{
    if(m_pCentral) {
        m_pLayout->removeWidget(m_pCentral);
        m_pCentral->deleteLater();
        m_pCentral = nullptr;
    }
    m_pCentral = widget;
    m_pLayout->addWidget(m_pCentral);
}

void CMainWindow::readSettings()
{
    QScreen* pScreen = qApp->primaryScreen();
    int w = pScreen->availableGeometry().width();
    int h = pScreen->availableGeometry().height();
    QSettings settings(QDir::currentPath() + "/config.ini", QSettings::IniFormat);
    settings.beginGroup("CMainWindow");
    resize(settings.value("size", QSize(w / 2, h / 2)).toSize());
    move(settings.value("pos", QPoint(w / 5, h / 10)).toPoint());
    settings.endGroup();
}

void CMainWindow::writeSettings()
{
    QSettings settings(QDir::currentPath() + "/config.ini", QSettings::IniFormat);
    qDebug(qPrintable(QDir::currentPath() + "/config.ini"));
    settings.beginGroup("CMainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

bool CMainWindow::isMoved()
{
    return m_bLockMoved;
}

bool CMainWindow::isLocked()
{
    return m_bLocked;
}

void CMainWindow::setLockMoved(bool flag)
{
    m_bLockMoved = flag;
}

void CMainWindow::setLocked(bool flag)
{
    m_bLocked = flag;
}

CTitleBar* CMainWindow::getTitleBar()
{
    return m_pTitleBar;
}

QStatusBar* CMainWindow::getStatusBar()
{
    return m_pStatus;
}

QSystemTrayIcon* CMainWindow::getQSystemTrayIcon()
{
    return m_pTrayIcon;
}

CFlyWindow* CMainWindow::getFlyWindow()
{
    return m_pFlyWin;
}

void CMainWindow::swithMaxNormal()
{
    isMaximized() ? showNormal() : showMaximized();
}

void CMainWindow::showFlyWindow()
{
    m_pFlyWin->show();
}

void CMainWindow::mousePressEvent(QMouseEvent *e)
{
    if(Qt::LeftButton == e->button())
    {
        if(e->y() < m_pTitleBar->height() && e->x() > m_pTitleBar->width() - 120)
        {
            m_bPressed = false;
        }
        else
        {
            m_qDragPos = e->globalPos() - frameGeometry().topLeft();
            m_bPressed = true;
        }
    }
    e->accept();
}

void CMainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->y() < m_pTitleBar->height() && e->x() < m_pTitleBar->width() - 120)
    {
        swithMaxNormal();
        e->accept();
    }else{
        e->ignore();
    }
}

void CMainWindow::SetCursorStyle(ENUM_DIRECTION direct)
{
    //设置上下左右以及右上、右下、左上、坐下的鼠标形状
    switch(direct)
    {
    case eTop:
    case eBottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case eRight:
    case eLeft:
        setCursor(Qt::SizeHorCursor);
        break;
    case eNormal:
        setCursor(Qt::ArrowCursor);
    }
}

void CMainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    m_pTitleBar->clearChecked();
    e->accept();
}

void CMainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(isMaximized())
    {
        e->ignore();
    }
    else
    {

        if(e->y() < m_pTitleBar->height() && e->x() > m_pTitleBar->width() - 120)
        {
            e->ignore();
        }
        else{
            if(m_bPressed)
            {
                if(getTitleBar()->getFixedflag())
                {
                    move(e->globalPos() - m_qDragPos);
                }
                e->accept();
            }

        }
    }

}

void CMainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape){
        close();
    }
    else if (e->key() == Qt::Key_F11) {
        m_pTitleBar->getMaxButton()->click();
    }
}

void CMainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    return QWidget::closeEvent(event);
}


void CMainWindow::animationClose()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
    animation->setDuration(1500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
}

void CMainWindow::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    //单击
    case QSystemTrayIcon::Trigger:
        //双击
    case QSystemTrayIcon::DoubleClick:
        if(isHidden())
        {
            //恢复窗口显示
            show();
            //一下两句缺一均不能有效将窗口置顶
            setWindowState(Qt::WindowActive);
            activateWindow();
            setLocked(m_bLocked);
        }
        else
        {
            if(!m_bLocked)
            {
                hide();
            }
        }
        break;
    case QSystemTrayIcon::Context:
        break;
    default:
        break;
    }
}

CMainWindow::~CMainWindow()
{

}
