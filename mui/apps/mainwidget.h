#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMap>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    QMap<QString, QWidget*> m_widMap;
    QMap<QString, Qt::DockWidgetArea> m_areaMap;
};
#endif // MAINWIDGET_H
