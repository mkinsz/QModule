#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cmainwindow.h"

class ThemeMenu;
class SettingMenu;
class CenterWindow;
class FloatWindow;
class QVBoxLayout;
class MainWindow : public CMainWindow
{
    Q_OBJECT

public:
    static MainWindow* window();
    FloatWindow* getFloatWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void initData();
    void initUi();
    void initEvt();

public:
    CenterWindow *m_pCenter = nullptr;
    FloatWindow *m_pFloat = nullptr;
    SettingMenu *m_pSettingMenu = nullptr;
    ThemeMenu   *m_pThemeMenu = nullptr;

private:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Q_DISABLE_COPY(MainWindow)

    static MainWindow* m_pInstance;
};
#endif // MAINWINDOW_H
