#ifndef CTOOLBUTTON_H
#define CTOOLBUTTON_H

#include <QToolButton>

class CToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit CToolButton(QWidget *parent = nullptr);
    ~CToolButton() override;

    void setMenu(QMenu *menu);

signals:

public slots:
    void onAboutToHide();

};

#endif // CTOOLBUTTON_H
