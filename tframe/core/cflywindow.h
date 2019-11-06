#ifndef CFLYWINDOW_H
#define CFLYWINDOW_H

#include <QWidget>

class QMenu;
class CFlyWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CFlyWindow(QWidget *parent = nullptr);

    void initData();
    void initUI();
    void initConnect();
    void setMenu(QMenu* menu);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    QWidget *m_pParent = nullptr;
    QMenu   *m_pSettingMenu = nullptr;

    QPoint m_CurrentPos;
    QPixmap m_Pixmap;
};

#endif // CFLYWINDOW_H
