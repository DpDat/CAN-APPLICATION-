#ifndef TOYOTA_DECODE_H
#define TOYOTA_DECODE_H

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

namespace Ui {
class Toyota_decode;
}

struct DecodeFrame {
    QString canID;
    QString specification;
    QString unit;
    QString data ;
    QString value;
};

class Toyota_decode : public QDialog
{
    Q_OBJECT

public:
    explicit Toyota_decode(QWidget *parent = nullptr);
    ~Toyota_decode();
    void updateTable(const QList<DecodeFrame>& messages);
private slots:
    void on_buttonReturn_2_clicked();

    void on_buttonHome_2_clicked();

    void on_btnPortsInfo_clicked();

    void on_btnCOMbps_clicked();

    void on_buttonOpen_2_clicked();

    void handleSerialData();

    void updateTableValue(const QString &specification, const QString &value);

    void on_buttonVehicleSpeed_clicked();

    void on_buttonSaveStart_clicked();

    void on_buttonSaveStop_clicked();

    void saveDataContinuously();

    void saveDataToFile(const QString &filePath);

private:
    Ui::Toyota_decode *ui;
    void loadPorts();


    QSerialPort *_serialPort;
    QSerialPortInfo info;

    graphwindow *graphWindow;

    QTimer *saveTimer;
    QStringList savedData;
};

#endif // TOYOTA_DECODE_H
