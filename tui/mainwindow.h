#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class Navigation;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
    void release();

private Q_SLOTS:
    void onClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QWidget *m_pContent, *m_pMedium = nullptr;
    Navigation *m_pView = nullptr;
};
#endif // MAINWINDOW_H
