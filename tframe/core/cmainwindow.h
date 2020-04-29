#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>

typedef enum {
    eLeft,
    eTop,
    eRight,
    eBottom,
    eNormal
} ENUM_DIRECTION;

class CTitleBar;
class CFlyWindow;
class QStatusBar;
class QVBoxLayout;
class CMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow() override;

    void initData();
    void initUi();
    void initEvt();

    QWidget *centralWidget();
    void setCentralWidget(QWidget* widget);

    CTitleBar* getTitleBar();
    QStatusBar* getStatusBar();
    QSystemTrayIcon* getQSystemTrayIcon();
    CFlyWindow* getFlyWindow();

    void animationClose();
    bool isMoved();
    bool isLocked();

signals:
    void Hidden();

public slots:
    void swithMaxNormal();
    void showFlyWindow();
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void setLockMoved(bool flag);
    void setLocked(bool flag);

protected:
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void closeEvent(QCloseEvent * event) override;

protected:
    void SetCursorStyle(ENUM_DIRECTION direct);
    void readSettings();
    void writeSettings();

private:
    QPoint m_qDragPos;

    bool m_bPressed;
    bool m_bLockMoved;
    bool m_bLocked;

    CTitleBar  *m_pTitleBar;
    QStatusBar *m_pStatus;
    CFlyWindow *m_pFlyWin;
    QSystemTrayIcon *m_pTrayIcon;

    QWidget *m_pCentral = nullptr;
    QVBoxLayout *m_pLayout = nullptr;
};

#endif // CMAINWINDOW_H
