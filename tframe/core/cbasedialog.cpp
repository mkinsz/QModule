#include "cbasedialog.h"
#include "ctitlebar.h"

#include <QVBoxLayout>

CBaseDialog::CBaseDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    initData();
    initUI();
    initConnect();
}

void CBaseDialog::initData()
{

}

void CBaseDialog::initUI()
{
    resize(0, 0);
    m_pTitleBar = new CTitleBar;
    m_pTitleBar->setSettingButtonVisible(false);
    m_pTitleBar->setSkinButtonVisible(false);
    m_pTitleBar->setFixButtonVisible(false);
    m_pTitleBar->setMinButtonVisible(false);
    m_pTitleBar->setMaxButtonVisible(false);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addWidget(m_pTitleBar);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void CBaseDialog::initConnect()
{

}

void CBaseDialog::animationClose()
{

}

void CBaseDialog::mouseMoveEvent(QMouseEvent *e)
{

}

void CBaseDialog::mousePressEvent(QMouseEvent *e)
{

}

void CBaseDialog::mouseReleaseEvent(QMouseEvent *e)
{

}

void CBaseDialog::showEvent(QShowEvent *event)
{

}

void CBaseDialog::closeEvent(QCloseEvent *event)
{

}
