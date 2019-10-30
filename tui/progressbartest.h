#ifndef DYNAMICPROGRESSBARTEST_H
#define DYNAMICPROGRESSBARTEST_H

#include <QWidget>

namespace Ui
{
class ProgressBarTest;
}

class ProgressBarTest : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressBarTest(QWidget *parent = nullptr);
    ~ProgressBarTest();

private:
    void connectToSlider(class RoundProgressBar *bar);
    void connectToBaseCircleCheckBox(class RoundProgressBar *bar);
    void connectToDataCircleCheckBox(class RoundProgressBar *bar);
    void connectToCenterCircleCheckBox(class RoundProgressBar *bar);
    void connectToTextCheckBox(class RoundProgressBar *bar);

private:
    Ui::ProgressBarTest *ui;
};

#endif // DYNAMICPROGRESSBARTEST_H
