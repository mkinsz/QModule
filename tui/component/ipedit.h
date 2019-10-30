#ifndef IPEDIT_H
#define IPEDIT_H

#include <QWidget>

class QSpinBox;
class QLabel;
class QHBoxLayout;

class IpEdit : public QWidget
{
    Q_OBJECT
public:
    explicit IpEdit(QWidget *parent = nullptr);
    ~IpEdit();

    QString getIpAddress();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

private slots:

private:
    QHBoxLayout *m_pLayout;  //主布局
    QSpinBox *m_pSpinBox[4]; //IP数字输入框
};

#endif // IPEDIT_H
