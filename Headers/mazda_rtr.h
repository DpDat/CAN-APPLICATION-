#ifndef MAZDA_RTR_H
#define MAZDA_RTR_H

#include <QDialog>
#include <QProcess>
#include <QTimer>
#include <QComboBox>
#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QCanBusDevice>
#include <QString>
#include <QMessageBox>
#include <QCanBusFrame>
#include <QList>
#include <QFont>
#include <QTableWidgetItem>
#include <QTimer>
#include <QCanBusFrame>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>


namespace Ui {
class Mazda_RTR;
}

class Mazda;

// Define the CANMessage structure
struct CANMessageTransmit {
    QString direction;
    QString canID;
    QString dlc;
    QString data;
};

struct CANMessageReceive
{
    QString CanID;
    QString DLC;
    QString DATA;
};

class Mazda_RTR : public QDialog
{
    Q_OBJECT

public:
    explicit Mazda_RTR(QWidget *parent = nullptr);
    ~Mazda_RTR();
    void updateTable(const QList<CANMessageTransmit>& messages);
    void updateTableReceive(const QList<CANMessageReceive>& messages);

    QList<CANMessageReceive> filterCANMessages(const QList<CANMessageReceive>& messages);


private slots:
    void on_buttonReturn_clicked();

    void on_btCANInterface_clicked();

    void on_BtnSetRequest_clicked();

    void sendCANFrame();

    void receiveCANFrame();

    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked();

    void on_buttonSave_clicked();

    void on_buttonOpen_clicked();

    void on_buttonHome_clicked();

private:

    QCanBusDevice *canDevice = nullptr;

    QTimer *transmitTimer;  // Add this line

    CANMessageTransmit currentCANMessage;

    CANMessageReceive receiveFrame;

    void startBackgroundProcess(const QString &command) ;

    void Delay(int milliseconds) ;


    Ui::Mazda_RTR *ui;
    Mazda *mazda;

    // Hai tiến trình QProcess để sử dụng cho mỗi bộ lọc
};

#endif // MAZDA_RTR_H
