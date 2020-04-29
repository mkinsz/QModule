#include "settingmenu.h"
#include "mainwindow.h"
#include "floatwindow.h"
#include "cflywindow.h"
#include "settingdialog.h"
#include "aboutdialog.h"

#include <QAction>
#include <QUrl>
#include <QApplication>
#include <QDesktopServices>

SettingMenu::SettingMenu(QWidget *parent) : QMenu(parent)
{
    initData();
    initUi();
    initEvt();
}

void SettingMenu::onTriggered(QAction *action)
{
    if("FlyWindow" == action->text()) {
        bool bv = MainWindow::window()->getFlyWindow()->isVisible();
        MainWindow::window()->getFlyWindow()->setVisible(!bv);
    }else if("FloatBar" == action->text()) {
        bool bv = MainWindow::window()->getFloatWindow()->isVisible();
        MainWindow::window()->getFloatWindow()->setVisible(!bv);
    }else if("Settings" == action->text()) {
        MainWindow::window()->show();
        SettingDialog* settingDialog = new SettingDialog;
        settingDialog->exec();
    }else if("Update" == action->text()) {
        QDesktopServices::openUrl(QUrl("https://github.com/mkinsz"));
    }else if("About" == action->text()) {
        MainWindow::window()->show();
        AboutDialog* aboutDialog = new AboutDialog;
        aboutDialog->exec();
    }else if("Quit" == action->text()) {
        MainWindow* p = MainWindow::window();
        p->animationClose();
    }
}

void SettingMenu::initData()
{
    m_names << "FlyWindow" << "FloatBar" << "Settings" << "Update" << "About" << "Quit";
}

void SettingMenu::initUi()
{
    for(auto item : m_names) {
        addAction(new QAction(item, this));
    }
}

void SettingMenu::initEvt()
{
    connect(this, &SettingMenu::triggered, this, &SettingMenu::onTriggered);
}
