#include "graphwindow.h"

graphwindow::graphwindow(QWidget *parent)
    : QDialog(parent)
    ,timeElapsed(0)

{

    this->setWindowTitle("Physical value plot");
    this->resize(600, 400);

    vehicleSpeedSeries = new QLineSeries();
    vehicleSpeedChart = new QChart();
    vehicleSpeedChart->addSeries(vehicleSpeedSeries);
    vehicleSpeedChart->createDefaultAxes();
    vehicleSpeedChart->axisX()->setTitleText("Time (s)");
    vehicleSpeedChart->axisY()->setTitleText("Vehicle Speed (Km/h)");
    vehicleSpeedChart->setTitle("Real-Time Vehicle Speed");

    engineSpeedSeries = new QLineSeries();
    engineSpeedChart = new QChart();
    engineSpeedChart->addSeries(engineSpeedSeries);
    engineSpeedChart->createDefaultAxes();
    engineSpeedChart->axisX()->setTitleText("Time (s)");
    engineSpeedChart->axisY()->setTitleText("Engine Speed (RPM)");
    engineSpeedChart->setTitle("Real-Time Engine Speed");

    WheelSpeed_FL = new QLineSeries();
    wheelFL = new QChart();
    wheelFL->addSeries(WheelSpeed_FL);
    wheelFL->createDefaultAxes();
    wheelFL->axisX()->setTitleText("Time (s)");
    wheelFL->axisY()->setTitleText("Wheel Speed FL (Km/h)");
    wheelFL->setTitle("Real-Time Wheel Speed FL");

    WheelSpeed_FR = new QLineSeries();
    wheelFR = new QChart();
    wheelFR->addSeries(WheelSpeed_FR);
    wheelFR->createDefaultAxes();
    wheelFR->axisX()->setTitleText("Time (s)");
    wheelFR->axisY()->setTitleText("Wheel Speed FR (Km/h)");
    wheelFR->setTitle("Real-Time Wheel Speed FR");

    WheelSpeed_RL = new QLineSeries();
    wheelRL = new QChart();
    wheelRL->addSeries(WheelSpeed_RL);
    wheelRL->createDefaultAxes();
    wheelRL->axisX()->setTitleText("Time (s)");
    wheelRL->axisY()->setTitleText("Wheel Speed RL (Km/h)");
    wheelRL->setTitle("Real-Time Wheel Speed RL");

    WheelSpeed_RR = new QLineSeries();
    wheelRR = new QChart();
    wheelRR->addSeries(WheelSpeed_RR);
    wheelRR->createDefaultAxes();
    wheelRR->axisX()->setTitleText("Time (s)");
    wheelRR->axisY()->setTitleText("Wheel Speed RR (Km/h)");
    wheelRR->setTitle("Real-Time Wheel Speed RR");

    chartView = new QChartView(vehicleSpeedChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

graphwindow::~graphwindow()
{
    delete ui;
}

void graphwindow::showVehicleSpeedChart()
{
    chartView->setChart(vehicleSpeedChart);
    this->setWindowTitle("Vehicle Speed");
    this->show();
}

void graphwindow::showWheelSpeedFLChart()
{
    chartView->setChart(wheelFL);
    this->setWindowTitle("Wheel Speed FL");
    this->show();
}

void graphwindow::showWheelSpeedFRChart()
{
    chartView->setChart(wheelFR);
    this->setWindowTitle("Wheel Speed FR");
    this->show();
}

void graphwindow::showWheelSpeedRLChart()
{
    chartView->setChart(wheelRL);
    this->setWindowTitle("Wheel Speed RL");
    this->show();
}

void graphwindow::showWheelSpeedRRChart()
{
    chartView->setChart(wheelRR);
    this->setWindowTitle("Wheel Speed RR");
    this->show();
}

void graphwindow::showEngineSpeedChart()
{
    chartView->setChart(engineSpeedChart);
    this->setWindowTitle("Engine Speed");
    this->show();
}
void graphwindow::updateVehicleSpeedPlot(double vehicleSpeed) {
    timeElapsed += 1.0;  // Increment time (assuming 1-second intervals)
    vehicleSpeedSeries->append(timeElapsed, vehicleSpeed);

    // Set the x-axis to display the last 10 seconds
    vehicleSpeedChart->axisX()->setRange(qMax(0.0, timeElapsed - 10), timeElapsed);

    // Optional: Adjust y-axis range if needed
    vehicleSpeedChart->axisY()->setRange(0, 300);  // range for speed
}


void graphwindow::updateEngineSpeedPlot(double enginespeed) {
    timeElapsed += 1.0;
    engineSpeedSeries->append(timeElapsed, enginespeed);

    engineSpeedChart->axisX()->setRange(qMax(0.0, timeElapsed - 10), timeElapsed);

    engineSpeedChart->axisY()->setRange(0, 10000);
}

void graphwindow::updateWheelSpeedFLPlot(double WheelFL){
    timeElapsed += 1.0;
    WheelSpeed_FL->append(timeElapsed, WheelFL);

    wheelFL->axisX()->setRange(qMax(0.0, timeElapsed - 10), timeElapsed);

    wheelFL->axisY()->setRange(0, 300);
}

void graphwindow::updateWheelSpeedFRPlot(double WheelFR){
    timeElapsed += 1.0;
    WheelSpeed_FR->append(timeElapsed, WheelFR);

    wheelFR->axisX()->setRange(qMax(0.0, timeElapsed - 10), timeElapsed);

    wheelFR->axisY()->setRange(0, 300);
}

void graphwindow::updateWheelSpeedRLPlot(double WheelRL){
    timeElapsed += 1.0;
    WheelSpeed_RL->append(timeElapsed, WheelRL);

    wheelRL->axisX()->setRange(qMax(0.0, timeElapsed - 10), timeElapsed);

    wheelRL->axisY()->setRange(0, 300);
}

void graphwindow::updateWheelSpeedRRPlot(double WheelRR){
    timeElapsed += 1.0;
    WheelSpeed_RR->append(timeElapsed, WheelRR);

    wheelRR->axisX()->setRange(qMax(0.0, timeElapsed - 10), timeElapsed);

    wheelRR->axisY()->setRange(0, 300);
}
