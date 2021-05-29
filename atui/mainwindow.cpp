#include "mainwindow.h"

#include "titlebar.h"
#include "frameless.h"
#include "systemtray.h"
#include "network.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QIcon>
#include <QSettings>
#include <QCloseEvent>
#include <QQuickWidget>
#include <QScreen>
#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    resize(1000,700);

    TitleBar *pTitleBar=new TitleBar(this);
    installEventFilter(pTitleBar);
    setWindowTitle("AT-Music");
    setWindowIcon(QIcon(":/res/music.png"));

    QDesktopWidget* pDesktop = qApp->desktop();
    int monitor = pDesktop->screenNumber(this);    //获取当前显示器编号
    QScreen* pScreen = qApp->screens()[monitor];
    setMinimumSize(1000,700);
    setMaximumSize(pScreen->availableSize());

    Frameless *pHelper = new Frameless(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(pTitleBar->height());   //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);                //设置窗体可移动
    pHelper->setWidgetResizable(true);              //设置窗体可缩放
    pHelper->setRubberBandOnMove(false);            //设置橡皮筋效果-不可移动
    pHelper->setRubberBandOnResize(false);          //设置橡皮筋效果-不可缩放

    QQuickWidget *pWidget=new QQuickWidget(this);
    pWidget->resize(this->width(),this->height()-pTitleBar->height());
    pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    qmlRegisterType<Network>("Network",1,0,"Network");

    pWidget->setSource(QUrl("qrc:/main.qml"));

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->setSpacing(0);
    pLayout->addWidget(pTitleBar);
    pLayout->addWidget(pWidget);
    pLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(pLayout);

    //系统托盘
    SystemTray *pSystemTray=new SystemTray(this);
    pSystemTray->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(0, 0, width(), height());

    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.fillPath(path, QBrush(QColor("#3D4D5A")));
    painter.drawPath(path);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("ATUI", "AT-MUSIC");
    settings.setValue("geometry", saveGeometry());
    this->hide();
    event->ignore();
}

