#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include <QMenu>

class SettingMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SettingMenu(QWidget *parent = nullptr);

signals:

public slots:
    void onTriggered(QAction *action);

private:
    void initData();
    void initUi();
    void initEvt();

private:
    QStringList     m_names;
};

#endif // SETTINGMENU_H
