#ifndef FRAMELESSHELPER_H
#define FRAMELESSHELPER_H

#include <QtGui>
#include <QBitmap>
#include <QPainter>
#include <QWidget>

namespace Helps{

class WidgetData;

class FramelessHelperPrivate
{
public:
    QHash<QWidget*, WidgetData*> m_widgetDataHash;
    bool m_bWidgetMovable       : true;
    bool m_bWidgetResizable     : true;
    bool m_bRubberBandOnResize  : true;
    bool m_bRubberBandOnMove    : true;
};

class CursorPosCalculator
{
public:
    explicit CursorPosCalculator();
    void reset();
    void recalculate(const QPoint &globalMousePos, const QRect &frameRect);

public:
    bool m_bOnEdges             : true;
    bool m_bOnLeftEdge          : true;
    bool m_bOnRightEdge         : true;
    bool m_bOnTopEdge           : true;
    bool m_bOnBottomEdge        : true;
    bool m_bOnTopLeftEdge       : true;
    bool m_bOnBottomLeftEdge    : true;
    bool m_bOnTopRightEdge      : true;
    bool m_bOnBottomRightEdge   : true;

    static int m_nBorderWidth;
    static int m_nTitleHeight;
};

class WidgetData
{
public:
    explicit WidgetData(FramelessHelperPrivate *d, QWidget *pTopLevelWidget);
    ~WidgetData();
    QWidget* widget();

    void handleWidgetEvent(QEvent *e);
    void updateRubberBandStatus();

private:
    void handleMousePressEvent(QMouseEvent *e);
    void handleMouseReleaseEvent(QMouseEvent *e);
    void handleMouseMoveEvent(QMouseEvent *e);
    void handleLeaveEvent(QEvent *e);
    void handleHoverMoveEvent(QHoverEvent *e);

    void moveWidget(const QPoint &gMousePos);
    void resizeWidget(const QPoint &gMousePos);
    void updateCursorShape(const QPoint &gMousePos);

private:
    FramelessHelperPrivate *d;
    QWidget *m_pWidget;
    QPoint m_ptDragPos;

    bool m_bLeftButtonPressed;
    bool m_bCursorShapeChanged;
    bool m_bLeftButtonTitlePressed;

    CursorPosCalculator m_pressedMousePos;
    CursorPosCalculator m_moveMousePos;

    Qt::WindowFlags m_windowFlags;
};

class FramelessHelper : public QObject
{
    Q_OBJECT

public:
    explicit FramelessHelper(QObject *parent = 0);
    ~FramelessHelper();

    void activateOn(QWidget *topLevelWidget);
    void removeFrom(QWidget *topLevelWidget);

    void setWidgetMovable(bool movable);
    void setWidgetResizable(bool resizable);
    void setRubberBandOnMove(bool movable);
    void setRubberBandOnResize(bool resizable);
    void setBorderWidth(uint width);
    void setTitleHeight(uint height);

    bool widgetResizable();
    bool widgetMovable();

    bool rubberBandOnMove();
    bool rubberBandOnResisze();

    uint borderWidth();
    uint titleHeight();

signals:
    void sig_doubleClick();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    FramelessHelperPrivate *d;
};

}

#endif // FRAMELESSHELPER_H
