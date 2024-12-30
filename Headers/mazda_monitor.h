#ifndef MAZDA_MONITOR_H
#define MAZDA_MONITOR_H

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
class Mazda_monitor;
}

// Define the CANMessage structure
struct CANMessage {
    QString direction;
    QString timeScale;
    QString canID;
    QString dlc;
    QString data;
};

class Mazda_monitor : public QDialog
{
    Q_OBJECT

public:
    explicit Mazda_monitor(QWidget *parent = nullptr);
    ~Mazda_monitor();

    // Declare the updateTable function here
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


private:

    void loadPorts();
    //void updateTable(const QList<CANMessage>& messages);

    QCanBusDevice *canDevice = nullptr;  // CAN device pointer
    void startBackgroundProcess(const QString &command);
    void Delay(int milliseconds);



    Ui::Mazda_monitor *ui;
};

#endif // MAZDA_MONITOR_H
