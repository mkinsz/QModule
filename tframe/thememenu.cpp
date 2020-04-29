#include "thememenu.h"
#include <QFile>
#include <QMenu>
#include <QApplication>
#include <QDebug>

ThemeMenu::ThemeMenu(QWidget *parent) : QMenu(parent)
{
    initData();
    initUi();
    initEvt();
}

void ThemeMenu::onTriggered(QAction *action)
{
    changeStyleFile("E:/work/code/qmodule/tframe/skin/" + action->text().toLower() + ".css");
//    changeStyleFile(":/skin/" + action->text().toLower() + ".css");
}

void ThemeMenu::initData()
{
    m_names << "Black" << "White" << "Color";
}

void ThemeMenu::initUi()
{
    QActionGroup *pGroup = new QActionGroup(this);
    pGroup->setExclusive(true);
    for (auto item : m_names) {
        QAction *pAct = new QAction(item, this);
        pAct->setCheckable(true);
        pGroup->addAction(pAct);
        m_actions.append(pAct);
    }

    addActions(m_actions);

    m_actions.first()->setChecked(true);
    changeStyleFile(":/skin/black.css");
}

void ThemeMenu::initEvt()
{
    connect(this, &ThemeMenu::triggered, this, &ThemeMenu::onTriggered);
}

void ThemeMenu::changeStyleFile(const QString &path)
{
    QFile f(path);
    if (!f.open(QFile::ReadOnly)) return;
    qApp->setStyleSheet(QLatin1String(f.readAll()));
    f.close();
}
