#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDockWidget>
#include <QTextEdit>

#include "mgrplugins.h"
#include "interfaces.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

