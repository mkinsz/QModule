#include "progressbartest.h"
#include "ui_progressbartest.h"

ProgressBarTest::ProgressBarTest(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::ProgressBarTest)
{
    ui->setupUi(this);
    ui->taichiWait->setFrontColor(QColor(24, 189, 155));
    ui->taichiWait->setBackColor(Qt::white);
    ui->taichiWait->setClockwiseRotate(false);
    ui->circleWait->setColor(QColor(46, 194, 163));
    ui->circleWait->setClockwiseRotate(false);
    ui->pieWait->setFrontColor(QColor(24, 189, 155));
    ui->pieWait->setBackColor(Qt::white);
    ui->pieWait->setClockwiseRotate(false);
    ui->lineWait->setColor(QColor(46, 194, 164));
    ui->lineWait->setClockwiseRotate(false);
    ui->donutWait->setFrontColor(QColor(24, 189, 155));
    ui->donutWait->setBackColor(Qt::white);
    ui->donutWait->setClockwiseRotate(false);
    ui->zoomCircleWait1->setColor(QColor(24, 189, 155));
    ui->zoomCircleWait1->setMinRadious(25);
    ui->zoomCircleWait1->setZoomDelta(5);
    ui->zoomCircleWait1->setZoomOut(true);
    ui->zoomCircleWait2->setColor(Qt::white);
    ui->zoomCircleWait2->setMinRadious(25);
    ui->zoomCircleWait2->setRadious(50);
    ui->zoomCircleWait2->setZoomDelta(5);
    ui->zoomCircleWait2->setZoomOut(true);

    //圆环
    ui->roundBar1->setFormat("%v");
    ui->roundBar1->setDecimals(0);
    connectToSlider(ui->roundBar1);
    connectToBaseCircleCheckBox(ui->roundBar1);
    connectToDataCircleCheckBox(ui->roundBar1);
    connectToCenterCircleCheckBox(ui->roundBar1);
    connectToTextCheckBox(ui->roundBar1);

    QGradientStops grandientPoints;
    grandientPoints << QGradientStop(0, Qt::red) << QGradientStop(1, Qt::yellow);
    ui->roundBar4->setStartAngle(RoundProgressBar::PositionLeft);
    ui->roundBar4->setDecimals(0);
    ui->roundBar4->setDataColors(grandientPoints);
    connectToSlider(ui->roundBar4);
    connectToBaseCircleCheckBox(ui->roundBar4);
    connectToDataCircleCheckBox(ui->roundBar4);
    connectToCenterCircleCheckBox(ui->roundBar4);
    connectToTextCheckBox(ui->roundBar4);

    //饼状
    ui->roundBar2->setStartAngle(RoundProgressBar::PositionRight);
    ui->roundBar2->setBarStyle(RoundProgressBar::StylePie);
    ui->roundBar2->setDecimals(0);
    connectToSlider(ui->roundBar2);
    connectToBaseCircleCheckBox(ui->roundBar2);
    connectToDataCircleCheckBox(ui->roundBar2);
    connectToCenterCircleCheckBox(ui->roundBar2);
    connectToTextCheckBox(ui->roundBar2);

    ui->roundBar5->setStartAngle(RoundProgressBar::PositionLeft);
    ui->roundBar5->setBarStyle(RoundProgressBar::StylePie);
    ui->roundBar5->setDecimals(0);
    connectToSlider(ui->roundBar5);
    connectToBaseCircleCheckBox(ui->roundBar5);
    connectToDataCircleCheckBox(ui->roundBar5);
    connectToCenterCircleCheckBox(ui->roundBar5);
    connectToTextCheckBox(ui->roundBar5);

    //线条
    ui->roundBar3->setStartAngle(RoundProgressBar::PositionTop);
    ui->roundBar3->setBarStyle(RoundProgressBar::StyleLine);
    ui->roundBar3->setOutlinePenWidth(4);
    ui->roundBar3->setDataPenWidth(4);
    ui->roundBar3->setDecimals(0);
    connectToSlider(ui->roundBar3);
    connectToBaseCircleCheckBox(ui->roundBar3);
    connectToDataCircleCheckBox(ui->roundBar3);
    connectToCenterCircleCheckBox(ui->roundBar3);
    connectToTextCheckBox(ui->roundBar3);

    ui->roundBar6->setStartAngle(RoundProgressBar::PositionTop);
    ui->roundBar6->setBarStyle(RoundProgressBar::StyleLine);
    ui->roundBar6->setDecimals(2);
    ui->roundBar6->setClockwise(false);
    ui->roundBar6->setOutlinePenWidth(18);
    ui->roundBar6->setDataPenWidth(10);
    connectToSlider(ui->roundBar6);
    connectToBaseCircleCheckBox(ui->roundBar6);
    connectToDataCircleCheckBox(ui->roundBar6);
    connectToCenterCircleCheckBox(ui->roundBar6);
    connectToTextCheckBox(ui->roundBar6);
}

ProgressBarTest::~ProgressBarTest()
{
    delete ui;
}

void ProgressBarTest::connectToSlider(RoundProgressBar *bar)
{
    bar->setRange(ui->valueSlider->minimum(), ui->valueSlider->maximum());
    bar->setValue(ui->valueSlider->value());
    connect(ui->valueSlider, SIGNAL(valueChanged(int)), bar, SLOT(setValue(int)));
}

void ProgressBarTest::connectToBaseCircleCheckBox(RoundProgressBar *bar)
{
    connect(ui->base_circle_ckb, SIGNAL(toggled(bool)), bar, SLOT(setBaseCircleVisible(bool)));
}

void ProgressBarTest::connectToDataCircleCheckBox(RoundProgressBar *bar)
{
    connect(ui->data_circle_ckb, SIGNAL(toggled(bool)), bar, SLOT(setDataCircleVisible(bool)));
}

void ProgressBarTest::connectToCenterCircleCheckBox(RoundProgressBar *bar)
{
    connect(ui->center_circle_ckb, SIGNAL(toggled(bool)), bar, SLOT(setCenterCircleVisible(bool)));
}

void ProgressBarTest::connectToTextCheckBox(RoundProgressBar *bar)
{
    connect(ui->text_ckb, SIGNAL(toggled(bool)), bar, SLOT(setTextVisible(bool)));
}
