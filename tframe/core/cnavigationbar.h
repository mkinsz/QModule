#ifndef CNAVIGATIONBAR_H
#define CNAVIGATIONBAR_H

#include <QFrame>
#include "ccenterwindow.h"

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

    void setHAlign(CCenterWindow::EDIR_ALIGNMENT direct);
    void setVAlign(CCenterWindow::EDIR_ALIGNMENT direct);

signals:
    void indexChanged(int i);

private slots:
    void setButtonChecked();

public:
    QStringList m_names;
    QList<QPushButton*> m_buttons;

private:
    QHBoxLayout* m_hLayout = nullptr;
    QVBoxLayout* m_vLayout = nullptr;

    int m_index;
};

#endif // CNAVIGATIONBAR_H
