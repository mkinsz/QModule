#ifndef SIDERBARTEST_H
#define SIDERBARTEST_H

#include <QWidget>

namespace Ui
{
class SiderBarTest;
}

class SiderBarTest : public QWidget
{
    Q_OBJECT

public:
    explicit SiderBarTest(QWidget *parent = nullptr);
    ~SiderBarTest();

private slots:
    void updateLabel(int index, QString str);

private:
    Ui::SiderBarTest *ui;
};

#endif // SIDERBARTEST_H
