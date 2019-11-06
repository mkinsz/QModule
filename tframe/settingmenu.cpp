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
    initUI();
    initConnect();
}

void SettingMenu::onTriggered(QAction *action)
{
    if("FlyWindow" == action->text()) {
        bool bv = MainWindow::getInstance()->getFlyWindow()->isVisible();
        MainWindow::getInstance()->getFlyWindow()->setVisible(!bv);
    }else if("FloatBar" == action->text()) {
        bool bv = MainWindow::getInstance()->getFloatWindow()->isVisible();
        MainWindow::getInstance()->getFloatWindow()->setVisible(!bv);
    }else if("Settings" == action->text()) {
        MainWindow::getInstance()->show();
        SettingDialog* settingDialog = new SettingDialog;
        settingDialog->exec();
    }else if("Update" == action->text()) {
        QDesktopServices::openUrl(QUrl("https://github.com/mkinsz"));
    }else if("About" == action->text()) {
        MainWindow::getInstance()->show();
        AboutDialog* aboutDialog = new AboutDialog;
        aboutDialog->exec();
    }else if("Quit" == action->text()) {
        MainWindow* p = MainWindow::getInstance();
        p->animationClose();
    }
}

void SettingMenu::initData()
{
    m_names << "Show FlyWindow" << "Show FloatBar" << "Settings" << "Update" << "About" << "Quit";
}

void SettingMenu::initUI()
{
    for(auto item : m_names) {
        addAction(new QAction(item, this));
    }
}

void SettingMenu::initConnect()
{
    connect(this, &SettingMenu::triggered, this, &SettingMenu::onTriggered);
}
