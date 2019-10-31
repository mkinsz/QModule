#pragma execution_character_set("utf-8")
#include "siderbar.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QtMath>
#include <QDebug>

SiderBar::SiderBar(QWidget *parent)
    : QWidget(parent)
{
    m_barStartColor = QColor(121, 121, 121);
    m_barEndColor = QColor(78, 78, 78);
    m_itemStartColor = QColor(46, 132, 243);
    m_itemEndColor = QColor(39, 110, 203);
    m_textColor = Qt::white;
    m_lineColor = QColor(255, 107, 107);
    m_barRadious = 0;
    m_itemRadious = 0;
    m_space = 15;
    m_lineWidth = 3;
    m_lineStyle = LineStyle::None;
    m_orientation = Qt::Horizontal;
    m_bKeyMove = false;
    m_currentIndex = -1;

    m_slideTimer = new QTimer(this);
    m_slideTimer->setInterval(5);
    connect(m_slideTimer, SIGNAL(timeout()), this, SLOT(doSlide()));
    m_shakeTimer = new QTimer(this);
    m_shakeTimer->setInterval(5);
    connect(m_shakeTimer, SIGNAL(timeout()), this, SLOT(doShake()));
    setFocusPolicy(Qt::ClickFocus);
}

SiderBar::~SiderBar()
{
}

void SiderBar::addItem(const QString &item)
{
    if (item.isEmpty()) return;

    foreach (auto i, m_items)
        if (item == i.first) return;

    m_items.append(qMakePair(item, QRectF()));
    update();
}

void SiderBar::addItems(const QStringList &items)
{
    foreach (auto item, items)
        addItem(item);
}

QStringList SiderBar::getItems() const
{
    QStringList items;
    foreach (auto item, m_items)
        items.append(item.first);

    return items;
}

void SiderBar::setBarColor(const QColor color)
{
    if (color == m_barStartColor && color == m_barEndColor) return;

    m_barStartColor = color;
    m_barEndColor = color;
    update();
}

void SiderBar::setBarColor(const QColor bColor, const QColor eColor)
{
    if (bColor == m_barStartColor && eColor == m_barEndColor) return;
    m_barStartColor = bColor;
    m_barEndColor = eColor;
    update();
}

void SiderBar::setItemColor(const QColor color)
{
    if (color == m_itemStartColor && color == m_itemEndColor) return;

    m_itemStartColor = color;
    m_itemEndColor = color;
    update();
}

void SiderBar::setItemColor(const QColor bColor, const QColor eColor)
{
    if (bColor == m_itemStartColor && eColor == m_itemEndColor) return;
    m_itemStartColor = bColor;
    m_itemEndColor = eColor;
    update();
}

void SiderBar::setTextColor(QColor color)
{
    if (color != m_textColor)
    {
        m_textColor = color;
        update();
    }
}

void SiderBar::setLineColor(QColor color)
{
    if (color != m_lineColor)
    {
        m_lineColor = color;
        update();
    }
}

void SiderBar::setBarRadius(int radius)
{
    if (radius < 0 || radius == m_barRadious) return;

    m_barRadious = radius;
    update();
}

void SiderBar::setItemRadius(int radius)
{
    if (radius < 0 || radius == m_itemRadious) return;

    m_itemRadious = radius;
    update();
}

void SiderBar::setSpace(int space)
{
    if (space < 0 || space == m_space) return;

    m_space = space;
    update();
}

void SiderBar::setLineWidth(int width)
{
    if (width < 0 || width == m_lineWidth) return;

    m_lineWidth = width;
    update();
}

void SiderBar::setLineStyle(SiderBar::LineStyle style)
{
    if (style == m_lineStyle) return;

    m_lineStyle = style;
    update();
}

void SiderBar::setOrientation(Qt::Orientation orientation)
{
    if (orientation == m_orientation) return;

    m_orientation = orientation;
    update();
}

void SiderBar::setEnableKeyMove(bool enable)
{
    if (enable != m_bKeyMove)
    {
        m_bKeyMove = enable;
    }
}

void SiderBar::moveToFirst()
{
    moveTo(0);
}

void SiderBar::moveToLast()
{
    moveTo(m_items.size() - 1);
}

void SiderBar::moveToPrevious()
{
    moveTo(m_currentIndex - 1);
}

void SiderBar::moveToNext()
{
    moveTo(m_currentIndex + 1);
}

void SiderBar::moveTo(int index)
{
    if (index >= 0 && index < m_items.count() && index != m_currentIndex)
    {
        if (index == m_currentIndex) return;

        emit itemClicked(index, m_items[index].first);

        if (m_currentIndex == -1)
            m_startRect = m_items[index].second;

        m_forward = index > m_currentIndex;
        m_currentIndex = index;
        m_stopRect = m_items[index].second;

        m_slideTimer->start();
    }
}

void SiderBar::moveTo(const QString str)
{
    foreach (auto item, m_items) {
        if(item.first == str) {
            int index = m_items.indexOf(item);
            if(m_currentIndex !=  index) {
                moveTo(index);
                break;
            }
        }
    }
}

void SiderBar::moveTo(const QPointF point)
{
    foreach (auto item, m_items) {
        if(item.second.contains(point)) {
            int index = m_items.indexOf(item);
            if(m_currentIndex !=  index) {
                moveTo(index);
                break;
            }
        }
    }
}

void SiderBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    drawBarBackground(&painter);
    drawItemBackground(&painter);
    drawItemLine(&painter);
    drawText(&painter);
}

void SiderBar::resizeEvent(QResizeEvent *event)
{
    int count = m_items.size();
    qreal dx = 0;
    qreal dy = 0;

    QFontMetrics fm(font());
    int textHeight = fm.height();
    int textWidth = textHeight*2 + m_space*2;
    if(!m_items.empty())
        textWidth = fm.horizontalAdvance(m_items[0].first)+m_space;

    if(Qt::Horizontal == m_orientation) setMinimumHeight(textHeight+m_space);
    else setFixedWidth(textWidth*2+m_space*2);

    for (int i = 0; i < count; ++i)
    {
        QPair<QString, QRectF> &itemData = m_items[i];
        if (Qt::Horizontal == m_orientation)
        {
            itemData.second.setTopLeft(QPointF(dx, 0));
            dx += width() * 1.0 /count;
            itemData.second.setBottomRight(QPointF(dx, height()));
        }
        else
        {
            itemData.second.setTopLeft(QPointF(0, dy));
            dy +=  textHeight + m_space;
            itemData.second.setBottomRight(QPointF(width(), dy));
            qDebug() << itemData.second;
        }
    }

    if(-1 != m_currentIndex) {
        m_startRect = m_items[m_currentIndex].second;
        m_stopRect = m_items[m_currentIndex].second;
    }

    return QWidget::resizeEvent(event);
}

void SiderBar::mousePressEvent(QMouseEvent *event)
{
    moveTo(event->pos());
    return QWidget::mousePressEvent(event);
}

void SiderBar::keyPressEvent(QKeyEvent *event)
{
    if (!m_bKeyMove)
        return QWidget::keyPressEvent(event);

    switch (event->key())
    {
    case Qt::Key_Home:
        moveToFirst();
        break;
    case Qt::Key_End:
        moveToLast();
        break;
    case Qt::Key_Up:
    case Qt::Key_Left:
        moveToPrevious();
        break;
    case Qt::Key_Down:
    case Qt::Key_Right:
        moveToNext();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void SiderBar::drawBarBackground(QPainter *p)
{
    p->save();
    p->setPen(Qt::NoPen);
    QLinearGradient linerGradient(QPointF(0, 0), QPointF(0, height()));
    linerGradient.setColorAt(0.0, m_barStartColor);
    linerGradient.setColorAt(1.0, m_barEndColor);
    p->setBrush(linerGradient);

    p->drawRoundedRect(rect(), m_barRadious, m_barRadious);
    p->restore();
}

void SiderBar::drawItemBackground(QPainter *p)
{
    if (m_startRect.isNull())
        return;
    p->save();
    QLinearGradient linerGradient(m_startRect.topLeft(), m_startRect.bottomRight());
    linerGradient.setColorAt(0.0, m_itemStartColor);
    linerGradient.setColorAt(1.0, m_itemEndColor);
    p->setPen(Qt::NoPen);
    p->setBrush(linerGradient);

    p->drawRoundedRect(m_startRect, m_itemRadious, m_itemRadious);
    p->restore();
}

void SiderBar::drawItemLine(QPainter *p)
{
    if (m_startRect.isNull())  return;

    QPointF p1, p2;
    switch (m_lineStyle)
    {
    case None:
        return;
    case ItemTop:
        p1 = m_startRect.topLeft();
        p2 = m_startRect.topRight();
        break;
    case ItemRight:
        p1 = m_startRect.topRight();
        p2 = m_startRect.bottomRight();
        break;
    case ItemBottom:
        p1 = m_startRect.bottomLeft();
        p2 = m_startRect.bottomRight();
        break;
    case ItemLeft:
        p1 = m_startRect.topLeft();
        p2 = m_startRect.bottomLeft();
        break;
    case ItemRect:
        p1 = m_startRect.topLeft();
        p2 = m_startRect.bottomRight();
        break;
    }
    p->save();
    QPen linePen;
    linePen.setColor(m_lineColor);
    linePen.setWidth(m_lineWidth);
    p->setPen(linePen);
    if (m_lineStyle == ItemRect)
    {
        p->drawRoundedRect(QRectF(p1, p2), m_itemRadious, m_itemRadious);
    }
    else
    {
        p->drawLine(p1, p2);
    }
    p->restore();
}

void SiderBar::drawText(QPainter *p)
{
    p->save();
    p->setPen(m_textColor);

    foreach (auto item, m_items)
        p->drawText(item.second, Qt::AlignCenter, item.first);

    p->restore();
}

void SiderBar::doSlide()
{
    if (m_space <= 0 || m_startRect == m_stopRect)
        return;
    int dx, dy;
    if (m_orientation == Qt::Horizontal)
    {
        dx = m_space / 2;
        dy = 0;
    }
    else
    {
        dx = 0;
        dy = m_space / 2;
    }
    if (m_forward)
    {
        m_startRect.adjust(dx, dy, dx, dy);
        if ((m_orientation == Qt::Horizontal && m_startRect.topLeft().x() >= m_stopRect.topLeft().x()) ||
                (m_orientation == Qt::Vertical && m_startRect.topLeft().y() >= m_stopRect.topLeft().y()))
        {
            m_slideTimer->stop();
            if (m_startRect != m_stopRect)
                m_shakeTimer->start();
        }
    }
    else
    {
        m_startRect.adjust(-dx, -dy, -dx, -dy);
        if ((m_orientation == Qt::Horizontal && m_startRect.topLeft().x() <= m_stopRect.topLeft().x()) ||
                (m_orientation == Qt::Vertical && m_startRect.topLeft().y() <= m_stopRect.topLeft().y()))
        {
            m_slideTimer->stop();
            if (m_startRect != m_stopRect)
                m_shakeTimer->start();
        }
    }
    update();
}

void SiderBar::doShake()
{
    qreal delta = 2.0;
    qreal dx1, dy1, dx2, dy2;
    dx1 = dy1 = dx2 = dy2 = 0.0;
    if (m_startRect.topLeft().x() > m_stopRect.topLeft().x())
    {
        dx1 = -delta;
    }
    else if (m_startRect.topLeft().x() < m_stopRect.topLeft().x())
    {
        dx1 = delta;
    }
    if (m_startRect.topLeft().y() > m_stopRect.topLeft().y())
    {
        dy1 = -delta;
    }
    else if (m_startRect.topLeft().y() < m_stopRect.topLeft().y())
    {
        dy1 = delta;
    }
    if (m_startRect.bottomRight().x() > m_stopRect.bottomRight().x())
    {
        dx2 = -delta;
    }
    else if (m_startRect.bottomRight().x() < m_stopRect.bottomRight().x())
    {
        dx2 = delta;
    }
    if (m_startRect.bottomRight().y() > m_stopRect.bottomRight().y())
    {
        dy2 = -delta;
    }
    else if (m_startRect.bottomRight().y() < m_stopRect.bottomRight().y())
    {
        dy2 = delta;
    }
    m_startRect.adjust(dx1, dy1, dx2, dy2);
    if (qAbs(m_startRect.topLeft().x() - m_stopRect.topLeft().x()) <= delta)
    {
        m_startRect.setLeft(m_stopRect.topLeft().x());
    }
    if (qAbs(m_startRect.topLeft().y() - m_stopRect.topLeft().y()) <= delta)
    {
        m_startRect.setTop(m_stopRect.topLeft().y());
    }
    if (qAbs(m_startRect.bottomRight().x() - m_stopRect.bottomRight().x()) <= delta)
    {
        m_startRect.setRight(m_stopRect.bottomRight().x());
    }
    if (qAbs(m_startRect.bottomRight().y() - m_stopRect.bottomRight().y()) <= delta)
    {
        m_startRect.setBottom(m_stopRect.bottomRight().y());
    }
    if (m_startRect == m_stopRect)
        m_shakeTimer->stop();
    update();
}
