#ifndef CNAVIGATIONBAR_H
#define CNAVIGATIONBAR_H

#include <QFrame>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class CNavigationBar : public QFrame
{
    Q_OBJECT
public:
    explicit CNavigationBar(QWidget *parent = nullptr);

    void initData();
    void initConnect();
    void initUI();
    int currentIndex();
    int count();
    void setCurrentIndex(int index);
    void addNavigationTile(const QString& tile, const QString &objectName);
    void setAlignTopLeft();
    void setAlignTopCenter();
    void setAlignTopRight();
    void setAlignBottomLeft();
    void setAlignBottomCenter();
    void setAlignBottomRight();
    void setAlignLeftTop();
    void setAlignLeftCenter();
    void setAlignLeftBottom();
    void setAlignRightTop();
    void setAlignRightCenter();
    void setAlignRightBottom();

signals:
    void indexChanged(int i);

private slots:
    void setButtonChecked();

public:
    QList<QPushButton*> m_buttons;

private:
    QHBoxLayout* m_topLeft = nullptr;
    QHBoxLayout* m_topCenter = nullptr;
    QHBoxLayout* m_topRight = nullptr;
    QHBoxLayout* m_bottomLeft = nullptr;
    QHBoxLayout* m_bottomCenter = nullptr;
    QHBoxLayout* m_bottomRight = nullptr;
    QVBoxLayout* m_leftTop = nullptr;
    QVBoxLayout* m_leftCenter = nullptr;
    QVBoxLayout* m_leftBottom = nullptr;
    QVBoxLayout* m_rightTop = nullptr;
    QVBoxLayout* m_rightCenter = nullptr;
    QVBoxLayout* m_rightBottom = nullptr;

    int m_index;
};

#endif // CNAVIGATIONBAR_H
