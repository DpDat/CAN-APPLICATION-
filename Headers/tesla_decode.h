#ifndef TESLA_DECODE_H
#define TESLA_DECODE_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QMap>
#include "graphwindow.h"
#include <QTimer>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QProcess>

namespace Ui {
class Tesla_decode;
}

struct DecodeFrame {
    QString canID;
    QString specification;
    QString unit;
    QString data ;
    QString value;
};

class Tesla_decode : public QDialog
{
    Q_OBJECT

public:
    explicit Tesla_decode(QWidget *parent = nullptr);
    ~Tesla_decode();
    void updateTable(const QList<DecodeFrame>& messages);
private slots:
    void on_buttonReturn_2_clicked();

    void on_buttonHome_2_clicked();

    void on_btnPortsInfo_clicked();

    void on_buttonOpen_2_clicked();

    void handleSerialData();

    void updateTableValue(const QString &specification, const QString &rawData, const QString &lastValue);

    void on_buttonVehicleSpeed_clicked();

    void on_buttonSaveStart_clicked();

    void on_buttonSaveStop_clicked();

    void saveDataContinuously();

    void saveDataToFile(const QString &filePath);

    void on_buttonEngineSpeed_clicked();

    void on_buttonWspeedFL_clicked();

    void on_buttonWspeedFR_clicked();

    void on_buttonWspeedRL_clicked();

    void on_buttonWspeedRR_clicked();

    void on_pushButton_clicked();

private:
    Ui::Tesla_decode *ui;
    void loadPorts();


    QSerialPort *_serialPort;
    QSerialPortInfo info;

    graphwindow *graphWindow;

    QTimer *saveTimer;
    QStringList savedData;
    void startPulseview();

};

#endif // TESLA_DECODE_H
