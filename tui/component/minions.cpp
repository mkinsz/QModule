#include "minions.h"
#include <QPixmap>
#include <QPainter>
#include <QDebug>

//https://mp.weixin.qq.com/s/f5kXGxIvOAdVmZ-rzBhGRQ

Minions::Minions(QWidget *parent) : QWidget(parent)
{

}

void Minions::initParams()
{
    bodyWidth = qMin(width()*1.0f, height() * BODY_WIDTH_HEIGHT_SCALE) * BODY_SCALE;
    bodyHeight = qMin(width()*1.0f, height() * BODY_WIDTH_HEIGHT_SCALE) / BODY_WIDTH_HEIGHT_SCALE * BODY_SCALE;

    mStrokeWidth = qMax(bodyWidth / 50, mStrokeWidth);
    offset = mStrokeWidth / 2;

    bodyRect.setLeft((width() - bodyWidth) / 2);
    bodyRect.setTop((height() - bodyHeight) / 2);
    bodyRect.setRight(bodyRect.left() + bodyWidth);
    bodyRect.setBottom(bodyRect.top() + bodyHeight);

    radius = bodyWidth / 2;
    footHeight = radius * 0.4333f;

    handsHeight =  (height() + bodyHeight) / 2   + offset - radius * 1.65f;
}

void Minions::resizeEvent(QResizeEvent *event)
{
    initParams();
}

void Minions::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap(size());  //将画布的大小设置为和widget一样的
    QPainter painter;  //在画布上常见一个画家
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.begin(&pixmap);
    painter.setBrush(colorBody);
    painter.setPen(QPen(colorStroke, mStrokeWidth));
    painter.drawRoundedRect(bodyRect, radius, radius);  //Body

    QRectF rect;
    rect.setLeft((width() - bodyWidth)/2 + offset);
    rect.setTop((height() + bodyHeight)/2 - radius * 2 + offset);
    rect.setRight(rect.left() + bodyWidth - offset*2 );
    rect.setBottom(rect.top() + radius * 2 - offset*2);

    painter.setBrush(colorClothes);
    painter.setPen(QPen(colorStroke, mStrokeWidth));
    painter.drawArc(rect, 0, 180);

    int h = (int) (radius * 0.5);
    int w = (int) (radius * 0.3);

    rect.setLeft(rect.left() + w);
    rect.setTop(rect.top()  + radius - h);
    rect.setRight(rect.right() - w);
    rect.setBottom(rect.top() + h);
    painter.setPen(colorClothes);
    painter.drawRect(rect);

    float pt0 = rect.left() - w;
    float pt1 = rect.top() + h;
    float pt2 = pt0+w;
    float pt3 = pt1-h;
    float pt4 =  pt2 - offset + (radius-w)*2;
    float pt5 =  pt3 - offset;
    float pt6 =  pt5 + h;

    QLineF pts[5];
    pts[0].setLine(pt0, pt1, pt2, pt1);
    pts[1].setLine(pt2, pt1+offset, pt2, pt3);
    pts[2].setLine(pt2 - offset, pt3, pt4, pt3);
    pts[3].setLine(pt4, pt5, pt4, pt5 + h);
    pts[4].setLine(pt4 - offset, pt6, pt4 - offset + w, pt6);

    painter.setPen(QPen(colorStroke, mStrokeWidth));
    painter.drawLines(pts, 5);

    painter.end();  //画完了
    painter.begin(this);  //在Widget上开始绘制
    painter.drawPixmap(0, 0, pixmap);  //在控件上绘制pixmap图像
}
