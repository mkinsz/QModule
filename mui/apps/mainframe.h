#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include <qsystemtrayicon.h>

#define AROUND_STRETCH_FLAG

namespace Helps {
 class FramelessHelper;
}

class QLabel;
class QPushButton;
class MainFrame : public QDialog
{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void slt_max_clicked();
    void slt_systray_active(QSystemTrayIcon::ActivationReason);

private:
    void initUi();
    void initStyle();
    void initSysIcon();

    QSystemTrayIcon *m_systrayIcon;
    QWidget *m_title_widget;
    QLabel *m_icon_label;
    QLabel *m_title_label;
    QPushButton *m_max_btn;
    QPushButton *m_min_btn;
    QPushButton *m_close_btn;
    QWidget *m_main_widget;
    Helps::FramelessHelper * m_framelessHelper;
};

#endif // MAINFRAME_H
