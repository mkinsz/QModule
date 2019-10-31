#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QSplitter>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QDebug>

#include "cpolygon.h"
#include "curvecharttest.h"
#include "ultrasound.h"
#include "progressbartest.h"
#include "siderbartest.h"
#include "navigationtest.h"
#include "treeviewtest.h"
#include "components.h"
#include "navigation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/stone.ico"));
    setWindowTitle("T-UI");

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QSplitter *pSplitter = new QSplitter(Qt::Horizontal, this);
    m_pView = new Navigation(pSplitter);
    m_pContent = new QWidget(pSplitter);
    m_pMedium = new Components(m_pContent);

    pSplitter->addWidget(m_pView);
    pSplitter->addWidget(m_pContent);
    pSplitter->setHandleWidth(3);
    pSplitter->setSizes({140, 700});

    QHBoxLayout *pLayout = new QHBoxLayout(m_pContent);
    pLayout->addWidget(m_pMedium);
    m_pContent->setLayout(pLayout);
    ui->centralLayout->addWidget(pSplitter);

    connect(m_pView, &QListView::clicked, this, &MainWindow::onClicked);

    m_pView->setIcoColorBg(false);
    m_pView->setColorLine(QColor(193, 193, 193));
    m_pView->setColorBg(QColor(255, 255, 255), QColor(232, 236, 245), QColor(242, 242, 242));
    m_pView->setColorText(QColor(19, 36, 62), QColor(19, 36, 62), QColor(19, 36, 62));
    m_pView->setInfoVisible(false);
    m_pView->readData(":/resources/config.xml");
    m_pView->setCurrentIndex(m_pView->model()->index(0, 0));
}

void MainWindow::release()
{
}

void MainWindow::onClicked(const QModelIndex &index)
{
    qDebug() << index.data(Qt::DisplayRole).toString();

    if (m_pMedium)
    {
        m_pContent->layout()->removeWidget(m_pMedium);
        m_pMedium->deleteLater();
        m_pMedium = nullptr;
    }

//    m_pMedium = new Components(m_pContent);
    m_pMedium = new SiderBarTest(m_pContent);

    if (m_pMedium)
        m_pContent->layout()->addWidget(m_pMedium);
}
