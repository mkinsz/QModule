#ifndef MINIONS_H
#define MINIONS_H

#include <QRectF>
#include <QColor>
#include <QWidget>

class Minions : public QWidget
{
    Q_OBJECT
public:
    explicit Minions(QWidget *parent = nullptr);

    void initParams();

signals:

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    float bodyWidth;
    float bodyHeight;

    float BODY_SCALE = 0.6f; // 身体主干占整个view的比重
    float BODY_WIDTH_HEIGHT_SCALE = 0.6f; // 身体的比例设定为 w:h = 3:5

    float mStrokeWidth = 4; // 描边宽度
    float offset; // 计算时，部分需要 考虑描边偏移
    float radius; // 身体上下半圆的半径

    QColor colorClothes = QColor(32, 116, 160); // 衣服的颜色
    QColor colorBody = QColor(249, 217, 70); // 身体的颜色
    QColor colorStroke = Qt::black;

    float handsHeight;// 计算出吊带的高度时，可以用来做手的高度
    float footHeight; // 脚的高度，用来画脚部阴影时用

    QRectF bodyRect;
};

#endif // MINIONS_H
