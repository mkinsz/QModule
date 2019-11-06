#ifndef CMOVEABLEWINDOW_H
#define CMOVEABLEWINDOW_H

#include <QFrame>

class CMoveableWindow : public QFrame
{
    Q_OBJECT
public:
    explicit CMoveableWindow(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QPoint m_dragPos;

    bool m_bPressed;
};

#endif // CMOVEABLEWINDOW_H
