#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QSplitter *pSplitter = new QSplitter(Qt::Horizontal, this);
    QListWidget *pView = new QListWidget(pSplitter);
    QStackedWidget *pStack = new QStackedWidget(pSplitter);

    pSplitter->addWidget(pView);
    pSplitter->addWidget(pStack);
    pSplitter->setHandleWidth(3);
    pSplitter->setSizes({150, 500});

    QStringList list;
    list<<"北京"<<"上海"<<"天津"<<"河北"<<"山东"<<"四川"<<"重庆"<<"广东"<<"河南";

    pView->addItems(list);
    pView->setCurrentIndex(pView->model()->index(0, 0));
    pView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->centralLayout->addWidget(pSplitter);
}

void MainWindow::release()
{

}

