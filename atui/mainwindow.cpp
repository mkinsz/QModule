#include "mainwindow.h"

#include "titlebar.h"
#include "frameless.h"
#include "systemtray.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QIcon>
#include <QSettings>
#include <QCloseEvent>
#include <QQuickWidget>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    resize(1000,700);

    TitleBar *pTitleBar=new TitleBar(this);
    installEventFilter(pTitleBar);
    setWindowTitle("ATUI");
    setWindowIcon(QIcon(":/res/logo.ico"));

    QDesktopWidget* pDesktop = qApp->desktop();
    int monitor = pDesktop->screenNumber(this);    //获取当前显示器编号
//    QWidget* pScreen = pDesktop->screen(monitor);
    setMinimumSize(1000,700);
    setMaximumSize(pDesktop->availableGeometry(monitor).width(),pDesktop->availableGeometry(monitor).height());

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

//    qmlRegisterType<Network>("Network",1,0,"Network");

    pWidget->setSource(QUrl(QStringLiteral(":/main.qml")));

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
    path.addRect(0, 0, this->width()-1, this->height()-1);

    QPainter painter(this);
    painter.setPen(Qt::lightGray);
    painter.fillPath(path, QBrush(Qt::white));
    painter.drawPath(path);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("ATUI", "ATMUSIC");
    settings.setValue("geometry", saveGeometry());
    this->hide();
    event->ignore();
}

