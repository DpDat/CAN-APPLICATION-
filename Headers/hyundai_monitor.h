#ifndef HYUNDAI_MONITOR_H
#define HYUNDAI_MONITOR_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
#include <QProcess>


namespace Ui {
class Hyundai_monitor;
}

struct CANMessage {
    QString direction;
    QString timeScale;
    QString canID;
    QString dlc;
    QString data;
};

class Hyundai_monitor : public QDialog
{
    Q_OBJECT

public:
    explicit Hyundai_monitor(QWidget *parent = nullptr);
    ~Hyundai_monitor();
     void updateTable(const QList<CANMessage>& messages);

private slots:
    void on_buttonHome_clicked();

    void on_buttonReturn_clicked();

    void on_btCANInterface_clicked();

    void on_btCANbps_clicked();

    void handleReceivedMessage();

    void on_buttonStop_clicked();

    void on_btCANFilter_clicked();

    void on_buttonSave_clicked();

    void on_buttonOpenFile_clicked();

    void on_pushButton_clicked();

private:
    Ui::Hyundai_monitor *ui;
    void loadPorts();
    //void updateTable(const QList<CANMessage>& messages);

    QCanBusDevice *canDevice = nullptr;  // CAN device pointer
    void startBackgroundProcess(const QString &command);
    void Delay(int milliseconds);
    void startPulseview();
};

#endif // HYUNDAI_MONITOR_H
