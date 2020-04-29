#ifndef THEMEMENU_H
#define THEMEMENU_H

#include <QMenu>

class ThemeMenu : public QMenu
{
    Q_OBJECT
public:
    explicit ThemeMenu(QWidget *parent = nullptr);

signals:

public slots:
    void onTriggered(QAction *action);

private:
    void initData();
    void initUi();
    void initEvt();

    void changeStyleFile(const QString& path);

private:
    QStringList m_names;
    QList<QAction*> m_actions;
};

#endif // THEMEMENU_H
