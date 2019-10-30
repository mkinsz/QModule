#ifndef NOTIFYBOX_H
#define NOTIFYBOX_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

class NotifyBox : public QWidget
{
    Q_OBJECT
public:
    explicit NotifyBox(int displayTime, QWidget *parent = nullptr);

    void setIcon(const QString &value);

    void setTitle(const QString &value);

    void setBody(const QString &value);

    void setUrl(const QString &value);

    void showGriant();

Q_SIGNALS:
    void disappeared();

private:
    int displayTime;

    QString icon;
    QString title;
    QString body;
    QString url;

    QLabel *backgroundLabel;
    QLabel *iconLabel;
    QLabel *titleLabel;
    QLabel *bodyLabel;

    QPushButton *closeBtn;

    void hideGriant();

    void mousePressEvent(QMouseEvent *event);
};

#endif // NOTIFYBOX_H
