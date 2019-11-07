#include "mainwindow.h"
#include "util.h"
#include "floatwindow.h"
#include "centerwindow.h"
#include "ctitlebar.h"
#include "cnavigationbar.h"
#include "ctoolbutton.h"
#include "cflywindow.h"
#include "thememenu.h"
#include "settingmenu.h"

#include <QMenu>
#include <QMouseEvent>
#include <QResizeEvent>

MainWindow* MainWindow::m_pInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : CMainWindow(parent)
{
    initData();
    initUI();
    initConnect();
}

MainWindow::~MainWindow()
{
    if(m_pFloat) {
        m_pFloat->deleteLater();
        m_pFloat = nullptr;
    }
}

MainWindow *MainWindow::getInstance()
{
    if(!m_pInstance)
        m_pInstance = new MainWindow;

    return m_pInstance;
}

void MainWindow::initData()
{
}

void MainWindow::initUI()
{
    m_pCenter = new CenterWindow(this);
    setCentralWidget(m_pCenter);
    m_pCenter->getNavigationBar()->setCurrentIndex(0);

    m_pSettingMenu = new SettingMenu(this);
    getTitleBar()->getSettingButton()->setMenu(m_pSettingMenu);
    getQSystemTrayIcon()->setContextMenu(m_pSettingMenu);
    getFlyWindow()->setMenu(m_pSettingMenu);

    m_pThemeMenu = new ThemeMenu(this);
    getTitleBar()->getSkinButton()->setMenu(m_pThemeMenu);

    m_pFloat = new FloatWindow;
}

void MainWindow::initConnect()
{
    connect(this, SIGNAL(Hidden()), m_pFloat, SLOT(hide()));
}

FloatWindow* MainWindow::getFloatWindow()
{
    return m_pFloat;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_pFloat->resize(m_pFloat->width(), event->size().height());
    m_pFloat->hide();

    return CMainWindow::resizeEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    m_pFloat->move(x() + width() + 2, y());

    return CMainWindow::mouseMoveEvent(event);
}

void MainWindow::showEvent(QShowEvent *event)
{
//    m_pFloat->setVisible(true);
    event->accept();
}

void MainWindow::hideEvent(QHideEvent *event)
{
//    m_pFloat->setVisible(false);
    event->accept();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->y() > getTitleBar()->height())
    {
        m_pFloat->setVisible(!m_pFloat->isVisible());
    }
    return CMainWindow::mouseDoubleClickEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        int index = m_pCenter->getNavigationBar()->currentIndex();
        int count = m_pCenter->getNavigationBar()->count();
        if(index == 0){
            m_pCenter->getNavigationBar()->setCurrentIndex(count - 1);
        }else if(index <= (count - 1) && index > 0){
            m_pCenter->getNavigationBar()->setCurrentIndex(index - 1);
        }
    }
    else if(event->key() == Qt::Key_Right)
    {
        int index = m_pCenter->getNavigationBar()->currentIndex();
        int count = m_pCenter->getNavigationBar()->count();
        if(index == (count - 1)){
            m_pCenter->getNavigationBar()->setCurrentIndex(0);
        }else if(index >= 0 && index < (count - 1)){
            m_pCenter->getNavigationBar()->setCurrentIndex(index + 1);
        }
    }
    else if(event->key() == Qt::Key_F1)
    {
        delete m_pCenter->getNavigationBar()->layout();
        m_pCenter->setAlignment(CCenterWindow::TopCenter);
    }
    else if(event->key() == Qt::Key_Space)
    {
        delete m_pCenter->getNavigationBar()->layout();
        int i = 1 + 12 * rand() / (RAND_MAX + 1);
        switch (i) {
        case 1:
            m_pCenter->setAlignment(CCenterWindow::TopLeft);
            break;
        case 2:
            m_pCenter->setAlignment(CCenterWindow::TopCenter);
            break;
        case 3:
            m_pCenter->setAlignment(CCenterWindow::TopRight);
            break;
        case 4:
            m_pCenter->setAlignment(CCenterWindow::RightTop);
            break;
        case 5:
            m_pCenter->setAlignment(CCenterWindow::RightCenter);
            break;
        case 6:
            m_pCenter->setAlignment(CCenterWindow::RightBottom);
            break;
        case 7:
            m_pCenter->setAlignment(CCenterWindow::BottomRight);
            break;
        case 8:
            m_pCenter->setAlignment(CCenterWindow::BottomCenter);
            break;
        case 9:
            m_pCenter->setAlignment(CCenterWindow::BottomLeft);
            break;
        case 10:
            m_pCenter->setAlignment(CCenterWindow::LeftBottom);
            break;
        case 11:
            m_pCenter->setAlignment(CCenterWindow::LeftCenter);
            break;
        case 12:
            m_pCenter->setAlignment(CCenterWindow::LeftTop);
            break;
        default:
            break;
        }
    }

    return CMainWindow::keyPressEvent(event);
}
