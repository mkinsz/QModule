#ifndef FLOATWINDOW_H
#define FLOATWINDOW_H

#include "cmoveablewindow.h"

class FloatWindow : public CMoveableWindow
{
    Q_OBJECT
public:
    explicit FloatWindow(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void showEvent(QShowEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void hideEvent(QHideEvent *event);

private:
    void initData();
    void initUI();
    void initConnect();

private:
    int m_width;
};

#endif // FLOATWINDOW_H
