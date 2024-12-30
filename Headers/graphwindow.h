#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
namespace Ui {
class graphwindow;
}

class graphwindow : public QDialog
{
    Q_OBJECT

public:
    explicit graphwindow(QWidget *parent = nullptr);
    ~graphwindow();

    void updateVehicleSpeedPlot(double vehicleSpeed);
    void updateEngineSpeedPlot(double enginespeed);
    void updateWheelSpeedFLPlot(double WheelFL);
    void updateWheelSpeedFRPlot(double WheelFR);
    void updateWheelSpeedRLPlot(double WheelRL);
    void updateWheelSpeedRRPlot(double WheelRR);

    void showVehicleSpeedChart();
    void showEngineSpeedChart();
    void showWheelSpeedFLChart();
    void showWheelSpeedFRChart();
    void showWheelSpeedRLChart();
    void showWheelSpeedRRChart();

private:

    QChart *vehicleSpeedChart;
    QChart *engineSpeedChart;
    QChart *wheelFL;
    QChart *wheelFR;
    QChart *wheelRL;
    QChart *wheelRR;
    QLineSeries *vehicleSpeedSeries;
    QLineSeries *engineSpeedSeries;
    QLineSeries *WheelSpeed_FL;
    QLineSeries *WheelSpeed_FR;
    QLineSeries *WheelSpeed_RL;
    QLineSeries *WheelSpeed_RR;
    QChartView *chartView;
    qreal timeElapsed;
    Ui::graphwindow *ui;
};

#endif // GRAPHWINDOW_H
