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
    m_itemTextColor = Qt::white;
    m_itemLineColor = QColor(255, 107, 107);
    m_barRadious = 0;
    m_itemRadious = 0;
    m_space = 25;
    m_itemLineWidth = 3;
    m_itemLineStyle = ItemLineStyle::None;
    m_orientation = Qt::Horizontal;
    m_bKeyMove = false;
    m_totalTextWidth = 0;
    m_totalTextHeight = 0;
    m_currentItemIndex = -1;
    m_bFixed = false;

    setAttribute(Qt::WA_TranslucentBackground);
    m_slideTimer = new QTimer(this);
    m_slideTimer->setInterval(10);
    connect(m_slideTimer, SIGNAL(timeout()), this, SLOT(doSlide()));
    m_shakeTimer = new QTimer(this);
    m_shakeTimer->setInterval(10);
    connect(m_shakeTimer, SIGNAL(timeout()), this, SLOT(doShake()));
    setFocusPolicy(Qt::ClickFocus);
}

SiderBar::~SiderBar()
{
}

void SiderBar::addItem(const QString &item)
{
    if (item.isEmpty()) return;

    QMap<int, QPair<QString, QRectF>>::iterator it = m_itemList.begin();
    while (it != m_itemList.end())
    {
        QPair<QString, QRectF> &itemData = it.value();
        if (item == itemData.first)
            return;
        ++it;
    }

    QFont f = font();
    QFontMetrics fm(f);
    int textWidth = fm.horizontalAdvance(item);
    int textHeight = fm.height();
    int itemCount = m_itemList.size();
    if (itemCount > 0)
    {
        QPointF topLeft, bottomRight;
        if (m_orientation == Qt::Horizontal)
        {
            topLeft = QPointF(m_totalTextWidth, 0);
            m_totalTextWidth += textWidth + m_space;
            bottomRight = QPointF(m_totalTextWidth, m_totalTextHeight);
        }
        else
        {
            topLeft = QPointF(0, m_totalTextHeight);
            m_totalTextHeight += textHeight + m_space;
            bottomRight = QPointF(m_totalTextWidth, m_totalTextHeight);
        }
        QRectF textRect(topLeft, bottomRight);
        m_itemList.insert(itemCount, qMakePair(item, textRect));
    }
    else
    {
        if (m_orientation == Qt::Horizontal)
        {
            m_totalTextWidth = textWidth + m_space;
            m_totalTextHeight = textHeight + m_space; //水平方向,水平占1个m_space,竖直占1个m_space
        }
        else
        {
            m_totalTextWidth = textWidth + 2 * m_space; //竖直方向,水平占2个m_space,竖直占1个m_space
            m_totalTextHeight = textHeight + m_space;
        }
        QPointF topLeft(0.0, 0.0);
        QPointF bottomRight(m_totalTextWidth, m_totalTextHeight);
        QRectF textRect(topLeft, bottomRight);
        m_itemList.insert(itemCount, qMakePair(item, textRect));
    }
    setMinimumSize(m_totalTextWidth, m_totalTextHeight);
    if (m_bFixed)
    {
        if (m_orientation == Qt::Horizontal)
            setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); //固定高度
        else
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred); //固定宽度
    }
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

    QMap<int, QPair<QString, QRectF>>::const_iterator it = m_itemList.begin();
    for (; it != m_itemList.end(); ++it)
        items.append(it.value().first);

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

void SiderBar::setItemTextColor(QColor color)
{
    if (color != m_itemTextColor)
    {
        m_itemTextColor = color;
        update();
    }
}

void SiderBar::setItemLineColor(QColor color)
{
    if (color != m_itemLineColor)
    {
        m_itemLineColor = color;
        update();
    }
}

void SiderBar::setBarRadious(uint radious)
{
    if (radious == m_barRadious) return;

    m_barRadious = radious;
    update();
}

void SiderBar::setItemRadious(uint radious)
{
    if (radious == m_itemRadious) return;

    m_itemRadious = radious;
    update();
}

void SiderBar::setSpace(uint space)
{
    if (space == m_space) return;

    m_space = space;
    update();
}

void SiderBar::setItemLineWidth(uint width)
{
    if (width == m_itemLineWidth) return;

    m_itemLineWidth = width;
    update();
}

void SiderBar::setItemLineStyle(SiderBar::ItemLineStyle style)
{
    if (style != m_itemLineStyle)
    {
        m_itemLineStyle = style;
        update();
    }
}

void SiderBar::setOrientation(Qt::Orientation orientation)
{
    if (orientation != m_orientation) return;

    m_orientation = orientation;
    update();
}

void SiderBar::setFixed(bool fixed)
{
    if (fixed != m_bFixed)
    {
        m_bFixed = fixed;
        update();
    }
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
    moveTo(m_itemList.size() - 1);
}

void SiderBar::moveToPrevious()
{
    moveTo(m_currentItemIndex - 1);
}

void SiderBar::moveToNext()
{
    moveTo(m_currentItemIndex + 1);
}

void SiderBar::moveTo(int index)
{
    if (index >= 0 && index < m_itemList.size() && index != m_currentItemIndex)
    {
        emit itemClicked(index, m_itemList[index].first);
        if (index == m_currentItemIndex)
            return;
        if (m_currentItemIndex == -1)
            m_startRect = m_itemList[index].second;
        m_forward = index > m_currentItemIndex;
        m_currentItemIndex = index;
        m_stopRect = m_itemList[index].second;
        m_slideTimer->start();
    }
}

void SiderBar::moveTo(const QString str)
{
    QMap<int, QPair<QString, QRectF>>::iterator it = m_itemList.begin();
    for (; it != m_itemList.end(); ++it)
    {
        if (it.value().first == str)
        {
            int targetIndex = it.key();
            if (targetIndex == m_currentItemIndex)
                return;
            moveTo(targetIndex);
            break;
        }
    }
}

void SiderBar::moveTo(const QPointF point)
{
    QMap<int, QPair<QString, QRectF>>::iterator it = m_itemList.begin();
    for (; it != m_itemList.end(); ++it)
    {
        if (it.value().second.contains(point))
        {
            int targetIndex = it.key();
            if (targetIndex == m_currentItemIndex)
                return;
            moveTo(targetIndex);
            break;
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
    if (m_bFixed) return;

    qreal addWidth, addHeight;
    if (m_orientation == Qt::Horizontal)
    {
        addWidth = 1.0 * (width() - m_totalTextWidth) / m_itemList.size();
        addHeight = 0;
    }
    else
    {
        addWidth = 0;
        addHeight = 1.0 * (height() - m_totalTextHeight) / m_itemList.size();
    }
    int itemCount = m_itemList.size();
    qreal dx = 0;
    qreal dy = 0;
    QPointF topLeft, bottomRight;
    for (int i = 0; i < itemCount; ++i)
    {
        QPair<QString, QRectF> &itemData = m_itemList[i];
        QFont f = font();
        QFontMetrics fm(f);
        int textWidth = fm.horizontalAdvance(itemData.first);
        int textHeight = fm.height();
        if (m_orientation == Qt::Horizontal)
        {
            topLeft = QPointF(dx, 0);
            dx += textWidth + m_space + addWidth;
            dy = m_totalTextHeight + addHeight;
        }
        else
        {
            topLeft = QPointF(0, dy);
            dx = m_totalTextWidth + addWidth;
            dy += textHeight + m_space + addHeight;
        }
        bottomRight = QPointF(dx, dy);
        QRectF textRect(topLeft, bottomRight);
        itemData.second = textRect;
        if (i == m_currentItemIndex)
        {
            m_startRect = textRect;
            m_stopRect = textRect;
        }
    }

    return QWidget::resizeEvent(event);
}

void SiderBar::mousePressEvent(QMouseEvent *event)
{
    QMap<int, QPair<QString, QRectF>>::iterator it = m_itemList.begin();
    for (; it != m_itemList.end(); ++it)
    {
        if (it.value().second.contains(event->pos()))
        {
            int targetIndex = it.key();
            emit itemClicked(targetIndex, it.value().first);
            if (targetIndex == m_currentItemIndex)
                return;
            if (m_currentItemIndex == -1)
            {
                m_startRect = it.value().second;
            }
            m_forward = targetIndex > m_currentItemIndex;
            m_currentItemIndex = targetIndex;
            m_stopRect = it.value().second;
            m_slideTimer->start();
            break;
        }
    }
}

void SiderBar::keyPressEvent(QKeyEvent *event)
{
    if (!m_bKeyMove)
    {
        QWidget::keyPressEvent(event);
        return;
    }
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
    if (m_startRect.isNull())
        return;
    QPointF p1, p2;
    switch (m_itemLineStyle)
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
    linePen.setColor(m_itemLineColor);
    linePen.setWidth(m_itemLineWidth);
    p->setPen(linePen);
    if (m_itemLineStyle == ItemRect)
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
    p->setPen(m_itemTextColor);
    QMap<int, QPair<QString, QRectF>>::iterator it = m_itemList.begin();
    while (it != m_itemList.end())
    {
        QPair<QString, QRectF> &itemData = it.value();
        p->drawText(itemData.second, Qt::AlignCenter, itemData.first);
        ++it;
    }
    p->restore();
}

void SiderBar::doSlide()
{
    if (m_space <= 0 || m_startRect == m_stopRect)
        return;
    qreal dx, dy;
    if (m_orientation == Qt::Horizontal)
    {
        dx = m_space / 2.0;
        dy = 0;
    }
    else
    {
        dx = 0;
        dy = m_space / 2.0;
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
