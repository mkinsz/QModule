#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT

    Q_PROPERTY(int itemWidth READ getItemWidth WRITE setItemWidth)
        Q_PROPERTY(int itemHeight READ getItemHeight WRITE setItemHeight)
        Q_PROPERTY(bool autoWidth READ getAutoWidth WRITE setAutoWidth)

public:
    explicit ComboBox(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *);

public:
    int getItemWidth()              const;
    int getItemHeight()             const;
    bool getAutoWidth()             const;

public Q_SLOTS:
    void setItemWidth(int itemWidth);
    void setItemHeight(int itemHeight);
    void setAutoWidth(bool autoWidth);

private:
    int itemWidth;                  //元素宽度
    int itemHeight;                 //元素高度
    bool autoWidth;                 //是否自动调整元素宽度
    int maxItemWidth;               //最大元素宽度
};
#endif // GRADIENTCOMBOBOX_H
