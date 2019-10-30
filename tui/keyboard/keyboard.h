#ifndef WIDGETKEYBOARD_H
#define WIDGETKEYBOARD_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class Keyboard : public QWidget
{
    Q_OBJECT
public:
    explicit Keyboard(QWidget *parent = nullptr);
    ~Keyboard();

signals:

public slots:

private:
    // 布局
    QHBoxLayout *horLyout[6];
    QVBoxLayout *verLayoutGlobal;
    QGridLayout *gridLayout;
    // 顶部
    QPushButton *btnTop[14];
    // 数字
    QPushButton *btnTopNumber[14];
    // 字母
    QPushButton *btnLetterQp[14];
    QPushButton *btnLetterAl[13];
    QPushButton *btnLetterZm[12];
    QPushButton *btnBottom[7];
    QPushButton *btnDirection[4];

private:
    void InitButtons();
    void SetStyleSheet();

protected:
    QPoint m_pointDrag;
    bool m_bLeftBtnPress;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent *);
};

#endif // WIDGETKEYBOARD_H
