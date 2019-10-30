#ifndef EXPANDERWIDGET_H
#define EXPANDERWIDGET_H

#include <QWidget>

class QPushButton;
class QStackedWidget;
class QVBoxLayout;

class Expander : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString expanderTitle READ expanderTitle WRITE setExpanderTitle STORED true)
    Q_PROPERTY(bool isExpanded READ isExpanded WRITE setExpanded STORED true)

public:
    Expander(QWidget *parent = nullptr);

    QSize sizeHint() const;

    int count() const;
    int currentIndex() const;
    QWidget *widget(int index);
    QString expanderTitle() const;
    bool isExpanded() const;

public slots:
    void onPressed();
    void setExpanderTitle(const QString &title);
    void setExpanded(bool flag);

    void addPage(QWidget *page);
    void insertPage(int index, QWidget *page);
    void removePage(int index);
    void setCurrentIndex(int index);

signals:
    void currentIndexChanged(int index);
    void expanderChanged(bool flag);

private:
    QPushButton *button;
    QStackedWidget *stackWidget;
    QVBoxLayout *layout;

    bool expanded = true;
};

#endif
