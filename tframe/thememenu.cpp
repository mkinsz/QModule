#include "thememenu.h"
#include <QFile>
#include <QMenu>
#include <QApplication>

ThemeMenu::ThemeMenu(QWidget *parent) : QMenu(parent)
{
    initData();
    initUI();
    initConnect();
}

void ThemeMenu::onTriggered(QAction *action)
{
    changeStyleFile(":/skin/" + action->text().toLower() + ".css");
}

void ThemeMenu::initData()
{
    m_names << "Black" << "White" << "Color";
}

void ThemeMenu::initUI()
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

void ThemeMenu::initConnect()
{
    connect(this, &ThemeMenu::triggered, this, &ThemeMenu::onTriggered);
}

void ThemeMenu::changeStyleFile(const QString &path)
{
    QFile f(path);
    if (!f.open(QFile::ReadOnly)) return;

    QString qss = QLatin1String(f.readAll());
    f.close();

    qApp->setStyleSheet(qss);
}
