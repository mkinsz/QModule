#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>

QT_BEGIN_NAMESPACE
class QImage;
class QPainter;
class QWidget;
class QPainterPath;
class QPoint;
class QRect;
class QString;
class QStringList;
QT_END_NAMESPACE

enum UNIT_TYPE {
    DOCKWIN,
    MDIAREA,
};

class UnitInterface
{
public:
    virtual ~UnitInterface() {}

    virtual QString name() const = 0;
    virtual QString iconPath() const = 0;
    virtual QWidget *widget() const = 0;
    virtual UNIT_TYPE unitType() const = 0;
    virtual Qt::DockWidgetArea dockArea() const = 0;
};

class DragInterface
{
public:
    virtual ~DragInterface() {}

    virtual QStringList brushes() const = 0;

    virtual QRect mousePress(const QString &brush, QPainter &painter,
                             const QPoint &pos) = 0;
    virtual QRect mouseMove(const QString &brush, QPainter &painter,
                            const QPoint &oldPos, const QPoint &newPos) = 0;
    virtual QRect mouseRelease(const QString &brush, QPainter &painter,
                               const QPoint &pos) = 0;
};

QT_BEGIN_NAMESPACE

#define UnitInterface_iid "org.MK.FramewareAndPlugin.UnitInterface"
#define DragInterface_iid "org.MK.FramewareAndPlugin.DragInterface"

Q_DECLARE_INTERFACE(UnitInterface, UnitInterface_iid)
Q_DECLARE_INTERFACE(DragInterface, DragInterface_iid)

QT_END_NAMESPACE

#endif // INTERFACES_H
