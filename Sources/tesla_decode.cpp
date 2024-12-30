#include "tesla_decode.h"
#include "ui_tesla_decode.h"
#include "tesla.h"
#include "mainwindow.h"
#include <QVBoxLayout>

Tesla_decode::Tesla_decode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Tesla_decode)
{
    ui->setupUi(this);
    this->setFixedSize(850,480);


    //ui->tableWidgetDecode->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetDecode->verticalHeader()->setVisible(true);
    ui->tableWidgetDecode->setColumnCount(5);
    ui->tableWidgetDecode->setRowCount(26);
    ui->tableWidgetDecode->setColumnWidth(0, 100); // Cột đầu tiên (CAN ID) có độ rộng 100 pixel
    ui->tableWidgetDecode->setColumnWidth(1, 180); // Cột Specification có độ rộng 150 pixel
    ui->tableWidgetDecode->setColumnWidth(2, 80);  // Cột Unit có độ rộng 80 pixel
    ui->tableWidgetDecode->setColumnWidth(3, 160); // Cột Data có độ rộng 200 pixel
    ui->tableWidgetDecode->setColumnWidth(4, 100); // Cột Value có độ rộng 100 pixel
    ui->tableWidgetDecode->setStyleSheet(
        "QTableWidget { border: 1px solid blue; } QHeaderView::section { background-color: gray; } QTableWidget::item { background-color: lightgray; }"
        "QTableWidget::item { "
        "border-top: 0.5px solid black; "
        "border-right: 0.5px solid black; "
        "border-bottom: 0.5px solid black; "
        "border-left: 0.5px solid black; "
        "}"
        );

    //add information into the table
    QList<DecodeFrame> infor = {
        {"0x118", "Pedal Position", "%", " ", " "},
        {"0x118", "Gear", "Level", " ", " "},
        {"0x129", "Steering Speed", "D/S", " ", " "},
        {"0x129", "Steering Angle", "Deg", " ", " "},
        {"0x132", "HV Battery Voltage", "V", " ", " "},
        {"0x132", "HV Battery Current", "A", " ", " "},
        {"0x1D8", "Rear Motor Torque", "Nm", " ", " "},
        {"0x201", "Battery Pump Actual RPM", "rpm", " ", " "},
        {"0x201", "Powertrain Pump Actual RPM", "rpm", " ", " "},
        {"0x201", "Superheat Actual Temperature", "°C", " ", " "},
        {"0x20C", "HVAC Blower Speed", "rpm", " ", " "},
        {"0x20C", "Evaporator Temperature", "°C", " ", " "},
        {"0x20C", "Evaporator Power", "W", " ", " "},
        {"0x241", "Battery Coolant Flow", "lpm", " ", " "},
        {"0x241", "Powertrain Coolant Flow", "lpm", " ", " "},
        {"0x257", "Vehicle Speed", "kph", " ", " "},
        {"0x273", "Wiper", "Mode", " ", " "},
        {"0x292", "State of Charge", "%", " ", " "},
        {"0x3B6", "Odometer", "km", " ", " "},
        {"0x3E2", "Left Signal Light", "ON/OFF", " ", " "},
        {"0x3E3", "Right Signal Light", "ON/OFF", " ", " "},
        {"0x321", "Outside Temperature", "°C", " ", " "},
        {"0x321", "Battery Coolant Temperature", "°C", " ", " "},
        {"0x321", "Powertrain Coolant Temperature", "°C", " ", " "},
        {"0x108", "Rear Axle Speed", "RPM", " ", " "},
        {"0x108", "Rear Axle Torque", "Nm", " ", " "},
                                };
    updateTable(infor);

    // Initialize the GraphWindow (initially hidden)
    graphWindow = new graphwindow(this);

    // Connect buttonVehicleSpeed to show the GraphWindow and start plotting
    connect(ui->buttonVehicleSpeed, &QPushButton::clicked, this, &Tesla_decode::on_buttonVehicleSpeed_clicked);
    connect(ui->buttonEngineSpeed, &QPushButton::clicked, this, &Tesla_decode::on_buttonEngineSpeed_clicked);
    connect(ui->buttonWspeedFL, &QPushButton::clicked, this, &Tesla_decode::on_buttonWspeedFL_clicked);
    connect(ui->buttonWspeedFR, &QPushButton::clicked, this, &Tesla_decode::on_buttonWspeedFR_clicked);
    connect(ui->buttonWspeedRL, &QPushButton::clicked, this, &Tesla_decode::on_buttonWspeedRL_clicked);
    connect(ui->buttonWspeedRR, &QPushButton::clicked, this, &Tesla_decode::on_buttonWspeedRR_clicked);

    // Initialize the timer for saving data
    saveTimer = new QTimer(this);
    connect(saveTimer, &QTimer::timeout, this, &Tesla_decode::saveDataContinuously);

    // Connect start and stop buttons
    connect(ui->buttonSaveStart, &QPushButton::clicked, this, &Tesla_decode::on_buttonSaveStart_clicked);
    connect(ui->buttonSaveStop, &QPushButton::clicked, this, &Tesla_decode::on_buttonSaveStop_clicked);
}


void Tesla_decode::updateTable(const QList<DecodeFrame>& messages)
{
    ui->tableWidgetDecode->clearContents();
    int row = 0;
    QFont customFont("Arial", 10, QFont::Bold);

    for (const DecodeFrame &msg : messages) {
        if (row >= ui->tableWidgetDecode->rowCount())
            break;

        QTableWidgetItem *canIDItem = new QTableWidgetItem(msg.canID);
        canIDItem->setFont(customFont);
        canIDItem->setForeground(Qt::blue);
        canIDItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetDecode->setItem(row, 0, canIDItem);

        QTableWidgetItem *SPECIFICATIONItem = new QTableWidgetItem(msg.specification);
        SPECIFICATIONItem->setFont(customFont);
        SPECIFICATIONItem->setForeground(Qt::darkGreen);
        SPECIFICATIONItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetDecode->setItem(row, 1, SPECIFICATIONItem);

        QTableWidgetItem *UnitItem = new QTableWidgetItem(msg.unit);
        UnitItem->setFont(customFont);
        UnitItem->setForeground(Qt::red);
        UnitItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetDecode->setItem(row, 2, UnitItem);

        QTableWidgetItem *candataItem = new QTableWidgetItem(msg.data);
        candataItem->setFont(customFont);
        candataItem->setForeground(Qt::blue);
        candataItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetDecode->setItem(row, 3, candataItem);

        QTableWidgetItem *ValueItem = new QTableWidgetItem(msg.value);
        ValueItem->setFont(customFont);
        ValueItem->setForeground(Qt::darkBlue);
        ValueItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetDecode->setItem(row, 4, ValueItem);
        row++;
    }
}
void Tesla_decode::on_buttonReturn_2_clicked()
{
    Tesla *tl;
    hide();
    tl=new Tesla(this);
    tl->show();
    if (_serialPort != nullptr && _serialPort->isOpen()) {
        _serialPort->close();
        qDebug() << "Port Disconnected: COM port has been disconnected.";
    }
    ui->cmbPorts->clear();
}


void Tesla_decode::on_buttonHome_2_clicked()
{
    MainWindow *md ;
    hide();
    md = new MainWindow(this);
    md->show();
    if (_serialPort != nullptr && _serialPort->isOpen()) {
        _serialPort->close();
        qDebug() << "Port Disconnected: COM port has been disconnected.";
    }
    ui->cmbPorts->clear();
}


void Tesla_decode::on_btnPortsInfo_clicked()
{
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->cmbPorts->addItems(stringPorts);
}

void Tesla_decode::loadPorts()
{
    foreach (auto &port, QSerialPortInfo::availablePorts() ) {
        ui->cmbPorts->addItem(port.portName());
    }
}

void Tesla_decode::on_buttonOpen_2_clicked()
{
    // If there is an existing serial port, close it and delete it
    if(_serialPort != nullptr)
    {
        _serialPort->close();
        delete _serialPort;
    }

    // Create a new serial port instance
    _serialPort = new QSerialPort(this);
    _serialPort->setPortName(ui->cmbPorts->currentText());
    _serialPort->setBaudRate(QSerialPort::Baud9600);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);

    // Open the serial port for reading and writing
    if(_serialPort->open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this,"Result","Port opened Successfully");
        // Send the string "Mazda" over the serial port
        QByteArray dataToSend = "3";
        _serialPort->write(dataToSend);

        if (_serialPort->waitForBytesWritten(1000))
        {
            qDebug() << "Data Sent: The string has been sent to the serial port.";
            connect(_serialPort, &QSerialPort::readyRead, this, &Tesla_decode::handleSerialData);
        }
        else
        {
            qDebug() << "Write Error: Failed to send string.";
        }

    } else {
        QMessageBox::critical(this,"Port Error","Unable to open specified port...");
    }
}


void Tesla_decode::handleSerialData() {
    static QByteArray buffer;
    buffer.append(_serialPort->readAll());

    int newlineIndex = buffer.indexOf('\n');
    while (newlineIndex != -1) {
        QByteArray line = buffer.left(newlineIndex).trimmed();
        buffer.remove(0, newlineIndex + 1);

        QList<QByteArray> messageParts = line.split(':');
        if (messageParts.size() == 2) {
            QString specification = messageParts[0].trimmed();
            QString rawData = messageParts[1].trimmed();

            QStringList rawDataParts = rawData.split(' ');
            QString lastValue = rawDataParts.isEmpty() ? "N/A" : rawDataParts.takeLast();

            if (graphWindow->isVisible()) {
                if (specification == "Vehicle speed") {
                    graphWindow->updateVehicleSpeedPlot(lastValue.toDouble());
                } else if (specification == "Engine speed") {
                    graphWindow->updateEngineSpeedPlot(lastValue.toDouble());
                } else if (specification == "Wheel speed (FL)") {
                    graphWindow->updateWheelSpeedFLPlot(lastValue.toDouble());
                } else if (specification == "Wheel speed (FR)") {
                    graphWindow->updateWheelSpeedFRPlot(lastValue.toDouble());
                } else if (specification == "Wheel speed (RL)") {
                    graphWindow->updateWheelSpeedRLPlot(lastValue.toDouble());
                } else if (specification == "Wheel speed (RR)") {
                    graphWindow->updateWheelSpeedRRPlot(lastValue.toDouble());
                }
            }

            QString modifiedRawData = rawDataParts.join(' ');
            updateTableValue(specification, modifiedRawData, lastValue);
        }
        newlineIndex = buffer.indexOf('\n');
    }
}

void Tesla_decode::updateTableValue(const QString &specification, const QString &rawData, const QString &lastValue) {
    static QMap<QString, QString> specificationDataMap;
    static QMap<QString, int> specificationRowMap; // Maps specifications to row indices

    if (specificationDataMap[specification] != rawData) {
        specificationDataMap[specification] = rawData;

        int row = -1;
        if (specificationRowMap.contains(specification)) {
            row = specificationRowMap[specification];
        } else {
            for (int i = 0; i < ui->tableWidgetDecode->rowCount(); ++i) {
                QTableWidgetItem *item = ui->tableWidgetDecode->item(i, 1);
                if (item && item->text() == specification) {
                    row = i;
                    specificationRowMap[specification] = i;
                    break;
                }
            }
        }

        if (row != -1) {
            QTableWidgetItem *dataItem = ui->tableWidgetDecode->item(row, 3);
            if (!dataItem) {
                dataItem = new QTableWidgetItem();
                ui->tableWidgetDecode->setItem(row, 3, dataItem);
            }
            dataItem->setText(rawData);

            QTableWidgetItem *valueItem = ui->tableWidgetDecode->item(row, 4);
            if (!valueItem) {
                valueItem = new QTableWidgetItem();
                ui->tableWidgetDecode->setItem(row, 4, valueItem);
            }
            valueItem->setText(lastValue);
        }
    }
}

void Tesla_decode::on_buttonVehicleSpeed_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showVehicleSpeedChart();
    }
}

void Tesla_decode::on_buttonEngineSpeed_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showEngineSpeedChart();
    }
}
void Tesla_decode::on_buttonWspeedRR_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedRRChart();
    }
}


void Tesla_decode::on_buttonWspeedRL_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedRLChart();
    }
}


void Tesla_decode::on_buttonWspeedFL_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedFLChart();
    }
}


void Tesla_decode::on_buttonWspeedFR_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedFRChart();
    }
}


void Tesla_decode::on_buttonSaveStart_clicked()
{
    if (!saveTimer->isActive()) {
        saveTimer->start(1000);  // Save data every 1 second (adjust interval as needed)
        QMessageBox::information(this, "Auto Save Started", "Data saving started automatically.");
    }
}
void Tesla_decode::saveDataContinuously() {
    QString dataRow;
    for (int row = 0; row < ui->tableWidgetDecode->rowCount(); ++row) {
        QString canID = ui->tableWidgetDecode->item(row, 0)->text();
        QString specification = ui->tableWidgetDecode->item(row, 1)->text();
        QString unit = ui->tableWidgetDecode->item(row, 2)->text();
        QString data = ui->tableWidgetDecode->item(row, 3)->text();
        QString value = ui->tableWidgetDecode->item(row, 4)->text();
        dataRow = canID + "," + specification + "," + unit + "," + data + "," + value;
        savedData.append(dataRow);
    }
}

void Tesla_decode::on_buttonSaveStop_clicked()
{
    if (saveTimer->isActive()) {
        saveTimer->stop();  // Stop the timer

        // Prompt user to choose where to save the file
        QString filePath = QFileDialog::getSaveFileName(this, "Save Data", "", "Text Files (*.csv);;All Files (*)");
        if (!filePath.isEmpty()) {
            saveDataToFile(filePath);
            QMessageBox::information(this, "Auto Save Stopped", "Data saved successfully to " + filePath);
        } else {
            QMessageBox::warning(this, "Save Canceled", "No file selected. Data was not saved.");
        }
        savedData.clear();  // Clear the saved data list after saving
    }
}

void Tesla_decode::saveDataToFile(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &line : savedData) {
            out << line << "\n";
        }
        file.close();
    } else {
        QMessageBox::critical(this, "Save Error", "Could not open file for saving.");
    }
}

Tesla_decode::~Tesla_decode()
{
    delete ui;
}
void Tesla_decode::startPulseview()
{
    QProcess *process = new QProcess();
    process->setProgram("pulseview");

    connect(process, &QProcess::readyReadStandardError, [process]() {
        qDebug() << "Pulseview error:" << process->readAllStandardError();
    });

    process->start();

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start pulseview:" << process->errorString();
    } else {
        qDebug() << "Pulseview started successfully.";
    }
}

void Tesla_decode::on_pushButton_clicked()
{
    startPulseview();
}
