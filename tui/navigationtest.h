#ifndef DEMO_NAVLISTVIEW_H
#define DEMO_NAVLISTVIEW_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class NavigationTest;
}

class NavigationTest : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationTest(QWidget *parent = nullptr);
    ~NavigationTest();

private:
    void initForm();

private:
    Ui::NavigationTest *ui;
};

#endif // DEMO_NAVLISTVIEW_H
