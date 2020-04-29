#ifndef CCENTERWINDOW_H
#define CCENTERWINDOW_H

#include <QWidget>
#include <QBoxLayout>

class CTitleBar;
class QBoxLayout;
class CNavigationBar;
class QStackedWidget;
class CCenterWindow : public QWidget
{
    Q_OBJECT
public:
    typedef enum {
        TopLeft,
        TopCenter,
        TopRight,
        RightTop,
        RightCenter,
        RightBottom,
        BottomRight,
        BottomCenter,
        BottomLeft,
        LeftBottom,
        LeftCenter,
        LeftTop,
    } EDIR_ALIGNMENT;

    typedef enum {
        AnimationTop,
        AnimationRight,
        AnimationBottom,
        AnimationLeft,
        AnimationTopLeft,
        AnimationTopRight,
        AnimationBottomRight,
        AnimationBottomLeft,
        AnimationCenter
    } EDIR_ANIMATION;

public:
    explicit CCenterWindow(QWidget *parent = nullptr);

    void initData();
    void initUi();
    void initEvt();
    void addWidget(const QString& tile, const QString &obejctName, QWidget* widget);
    void setAlignment(EDIR_ALIGNMENT direction);
    CNavigationBar* getNavigationBar();

signals:

public slots:
    void switchscreen(const int index);
    void switchscreen();
    void swicthLayout(QBoxLayout::Direction direction);
    virtual void cloudAntimation(EDIR_ANIMATION direction);

private:
    CNavigationBar  *m_pNavigation;
    QStackedWidget  *m_pStacked;
    CTitleBar       *m_pTitleBar;
    QBoxLayout      *m_pLayout;

    int m_curIndex;
    int m_preIndex;
};

#endif // CCENTERWINDOW_H
