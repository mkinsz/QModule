#ifndef GO2D_H
#define GO2D_H

#include <QQuickItem>

class Go2D : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Go2D)

public:
    explicit Go2D(QQuickItem *parent = nullptr);
    ~Go2D() override;
};

#endif // GO2D_H
