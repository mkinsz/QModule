#ifndef CBASEDIALOG_H
#define CBASEDIALOG_H

#include <QDialog>

class CTitleBar;
class CBaseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CBaseDialog(QWidget *parent = nullptr);

    void initData();
    void initUi();
    void initEvt();

signals:

public slots:
   virtual void animationClose();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void showEvent(QShowEvent * event);
    void closeEvent(QCloseEvent * event);

private:
    CTitleBar *m_pTitleBar;

    QPoint m_dragPos;

};

#endif // CBASEDIALOG_H
