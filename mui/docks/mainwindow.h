#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initForm();
    void loadPlugins();
    void loadPluginWidgets();

    QDockWidget *dockWidget(QWidget *pWidget);

private Q_SLOTS:
    void onTriggerAction(QAction *pAction);

private:
    Ui::MainWindow *ui;

    QMap<QString, QWidget*> m_widgetMap;
    QMap<QString, Qt::DockWidgetArea> m_dockAreaMap;
};
#endif // MAINWINDOW_H
