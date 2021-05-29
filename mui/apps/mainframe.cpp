#include "mainframe.h"

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>

#include "helps/helps.h"
#include "helps/framelesshelper.h"
#include "mainwidget.h"

MainFrame::MainFrame(QWidget *parent) : QDialog(parent)
{
    initUi();
    initSysIcon();
    initStyle();
}

void MainFrame::initUi()
{
    setObjectName("main_frame");
    m_title_widget = new QWidget(this);
    m_title_widget->setObjectName("widget_title");
    m_title_widget->setFixedHeight(32);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setSpacing(0);
    hlayout->setMargin(0);
    m_icon_label = new QLabel(this);
    m_icon_label->setObjectName("lab_icon");
    m_icon_label->setFixedSize(32, 32);
    m_title_label = new QLabel(this);
    m_title_label->setText("Title");
    m_title_label->setObjectName("lab_title");
    m_max_btn = new QPushButton(this);
    m_max_btn->setObjectName("btn_max");
    m_max_btn->setFixedSize(32, 32);
    m_min_btn = new QPushButton(this);
    m_min_btn->setObjectName("btn_min");
    m_min_btn->setFixedSize(32, 32);
    m_close_btn = new QPushButton(this);
    m_close_btn->setObjectName("btn_close");
    m_close_btn->setFixedSize(32, 32);
    hlayout->addSpacing(8);
    hlayout->addWidget(m_icon_label);
    hlayout->addWidget(m_title_label);
    hlayout->addWidget(m_min_btn);
    hlayout->addWidget(m_max_btn);
    hlayout->addWidget(m_close_btn);
    m_title_widget->setLayout(hlayout);

    m_main_widget = new MainWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    vlayout->addWidget(m_title_widget);
    vlayout->addWidget(m_main_widget);
    setLayout(vlayout);
    resize(1080, 680);
}

void MainFrame::initStyle()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setSizeGripEnabled(true);
#ifndef AROUND_STRETCH_FLAG
    this->setProperty("CanMove", true);
#else
    m_framelessHelper = new Helps::FramelessHelper(this);
    m_framelessHelper->activateOn(this);
    m_framelessHelper->setTitleHeight(32);
    m_framelessHelper->setWidgetMovable(true);
    m_framelessHelper->setWidgetResizable(true);
    m_framelessHelper->setRubberBandOnMove(true);
    m_framelessHelper->setRubberBandOnResize(true);
    connect(m_framelessHelper, SIGNAL(sig_doubleClick()), this, SLOT(slt_max_clicked()));
#endif

    setWindowTitle(m_title_label->text());

    m_title_label->installEventFilter(this);
    Helps::App::instance()->setIcon(m_close_btn, QChar(0xf00d));
    Helps::App::instance()->setIcon(m_max_btn, QChar(0xf2d0));
    Helps::App::instance()->setIcon(m_min_btn, QChar(0xf068));

    QIcon title_icon(":/res/img/logo.ico");
    QPixmap pixmap = title_icon.pixmap(QSize(16, 16));
    m_icon_label->setPixmap(pixmap);
    setWindowIcon(title_icon);

    Helps::App::moveFormToCenter(this);

    connect(m_close_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_min_btn, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(m_max_btn, SIGNAL(clicked()), this, SLOT(slt_max_clicked()));
    connect(m_min_btn, SIGNAL(clicked()), m_systrayIcon, SLOT(show()));
    connect(m_systrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slt_systray_active(QSystemTrayIcon::ActivationReason)));
}

void MainFrame::initSysIcon()
{
    m_systrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/res/img/logo.ico");
    m_systrayIcon->setIcon(icon);
    m_systrayIcon->setToolTip("MainFrame");
}

bool MainFrame::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->slt_max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void MainFrame::slt_max_clicked()
{
    if (!isMaximized()) {
        showMaximized();
        Helps::App::instance()->setIcon(m_max_btn, QChar(0xf2d0));
        m_max_btn->setToolTip("最大化");
#ifndef AROUND_STRETCH_FLAG
        this->setProperty("CanMove", false);
#endif
    } else {
        showNormal();
        Helps::App::instance()->setIcon(m_max_btn, QChar(0xf2d2));
        m_max_btn->setToolTip("还原");
#ifndef AROUND_STRETCH_FLAG
        this->setProperty("CanMove", true);
#endif
    }
}

void MainFrame::slt_systray_active(QSystemTrayIcon::ActivationReason reson)
{
    if(reson == QSystemTrayIcon::Trigger)
        this->showNormal();
}


