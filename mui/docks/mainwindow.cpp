#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interfaces.h"
#include "mgrplugins.h"

#include <QTextEdit>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initForm();
    loadPlugins();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initForm()
{
    setMinimumSize(1024, 768);
    connect(ui->toolBar, SIGNAL(actionTriggered(QAction*)), SLOT(onTriggerAction(QAction*)));
}

void MainWindow::loadPlugins()
{
    auto mgr = new MgrPlugins(this);
    QMap<QString, UnitInterface*> map = mgr->plugins();
    QMap<QString, UnitInterface*>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        i.value()->widget()->setWindowTitle(i.key());
        m_widgetMap[i.key()] = i.value()->widget();
        m_dockAreaMap[i.key()] = i.value()->dockArea();

        if(i.value()->unitType() == UNIT_TYPE::MDIAREA){
            ui->toolBar->addAction(QIcon(i.value()->iconPath()),i.value()->name());
            ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        }
        if(i.value()->unitType() == UNIT_TYPE::DOCKWIN){
            addDockWidget(i.value()->dockArea(), dockWidget(i.value()->widget()));
            ui->menuView->addAction(dockWidget(i.value()->widget())->toggleViewAction());

        }
        ++i;
    }
    ui->toolBar->toolButtonStyleChanged(Qt::ToolButtonTextUnderIcon);
    delete mgr;
}

void MainWindow::loadPluginWidgets()
{
    auto mgr = new MgrPlugins(this);
    auto map = mgr->plugins();
    auto i = map.constBegin();
    while(i != map.constEnd()) {
        m_widgetMap[i.key()] = i.value()->widget();
        m_dockAreaMap[i.key()] = i.value()->dockArea();

        ++i;
    }

    delete mgr;
}

QDockWidget *MainWindow::dockWidget(QWidget *pWidget)
{
    auto dock = new QDockWidget(pWidget->windowTitle());
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setWidget(pWidget);
    return dock;
}

void MainWindow::onTriggerAction(QAction *pAction)
{
    auto wins = ui->mdiArea->subWindowList();
    if(wins.count() != 0) {
        for(int i = 0; i < wins.count(); ++i) {
            if(wins[i]->windowTitle() == pAction->text()) return;
        }
    }

    ui->mdiArea->addSubWindow(m_widgetMap[pAction->text()], Qt::SubWindow);

    m_widgetMap[pAction->text()]->setWindowIcon(pAction->icon());
    m_widgetMap[pAction->text()]->setWindowTitle(pAction->text());
    m_widgetMap[pAction->text()]->show();

    loadPluginWidgets();
}

