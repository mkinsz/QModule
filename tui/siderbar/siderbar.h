#ifndef SLIDENAVATION_H
#define SLIDENAVATION_H

#include <QWidget>
#include <QVector>

#ifdef MSC
#if (QT_VERSION < QT_VERSION_CHECK(5, 7, 0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif
class QDESIGNER_WIDGET_EXPORT SiderBar : public QWidget
#else
class SiderBar : public QWidget
#endif
{
    Q_OBJECT
    Q_PROPERTY(SiderBar::LineStyle LineStyle READ getLineStyle WRITE setLineStyle)
    Q_PROPERTY(QStringList Items READ getItems WRITE addItems)
    Q_PROPERTY(int CurrentIndex READ getCurrentIndex WRITE setCurrentIndex)
public:
    enum LineStyle
    {
        None,       //不显示
        ItemTop,    //上方
        ItemRight,  //右方
        ItemBottom, //下方
        ItemLeft,   //左方
        ItemRect,   //矩形
    };

    explicit SiderBar(QWidget *parent = nullptr);
    ~SiderBar() override;

    void addItem(const QString &item);
    void addItems(const QStringList &items);
    QStringList getItems() const;

    void setBarColor(const QColor color);
    void setBarColor(const QColor bColor, const QColor eColor);
    void setItemColor(const QColor color);
    void setItemColor(const QColor bColor, const QColor eColor);

    void setTextColor(QColor color);
    void setLineColor(QColor color);
    void setBarRadius(int radius);
    void setItemRadius(int radius);
    void setSpace(int space);
    void setLineWidth(int width);
    LineStyle getLineStyle() const { return m_lineStyle; }
    void setLineStyle(LineStyle style);
    void setOrientation(Qt::Orientation orientation);
    int getCurrentIndex() const { return m_currentIndex; }

signals:
    void itemClicked(int index, QString str);

public slots:
    void setEnableKeyMove(bool enable);
    void moveToFirst();
    void moveToLast();
    void moveToPrevious();
    void moveToNext();
    void moveTo(int index);
    void moveTo(const QString str);
    void moveTo(const QPointF point);
    void setCurrentIndex(int index) { moveTo(index); }

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void drawBarBackground(QPainter *p);  //背景
    void drawItemBackground(QPainter *p); //当前选中Item背景
    void drawItemLine(QPainter *p);       //ItemLine
    void drawText(QPainter *p);           //all item text

private slots:
    void doSlide(); //滑动
    void doShake(); //晃动

private:
    QColor m_barStartColor; //背景色
    QColor m_barEndColor;
    QColor m_itemStartColor; //Item颜色
    QColor m_itemEndColor;
    QColor m_textColor;        //Item文字颜色
    QColor m_lineColor;        //Item线条指示器颜色
    int m_barRadious;              //边框圆角
    int m_itemRadious;             //Item圆角
    int m_space;                   //Item间隔
    int m_lineWidth;           //Item线条宽度
    LineStyle m_lineStyle; //Item线条类型
    Qt::Orientation m_orientation; //导航方向
    bool m_bKeyMove;               //按键移动

    QVector<QPair<QString, QRectF>> m_items;

    int m_currentIndex;     //当前选中item
    QRectF m_startRect;     //移动开始
    QRectF m_stopRect;      //移动结束
    QTimer *m_slideTimer;   //移动定时器
    QTimer *m_shakeTimer;   //晃动定时器
    bool m_forward;         //前进
};

#endif // SLIDENAVATION_H
