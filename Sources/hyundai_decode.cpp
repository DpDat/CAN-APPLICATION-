#include "hyundai_decode.h"
#include "ui_hyundai_decode.h"
#include "hynndai.h"
#include "mainwindow.h"
#include <QVBoxLayout>

Hyundai_decode::Hyundai_decode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Hyundai_decode)
{
    ui->setupUi(this);
    this->setFixedSize(750,480);


    ui->tableWidgetDecode->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetDecode->verticalHeader()->setVisible(true);
    ui->tableWidgetDecode->setColumnCount(5);
    ui->tableWidgetDecode->setRowCount(7);
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
                                {"0x541", "Left turn switch", "ON/OFF", " ", " "},
                                {"0x541", "Right turn switch", "ON/OFF", " ", " "},
                                {"0x541", "Flasher", "ON/OFF", " ", " "},
                                {"0x541", "Fog light", "ON/OFF", " ", " "},
                                {"0x541", "Head Light", "Mode", " ", " "},
                                {"0x541", "Wiper", "Mode", " ", " "},
                                {"0x541", "Hazard", "ON/OFF", " ", " "}
                                };
    updateTable(infor);

    // Initialize the GraphWindow (initially hidden)
    graphWindow = new graphwindow(this);

    // Connect buttonVehicleSpeed to show the GraphWindow and start plotting
    connect(ui->buttonVehicleSpeed, &QPushButton::clicked, this, &Hyundai_decode::on_buttonVehicleSpeed_clicked);
    connect(ui->buttonEngineSpeed, &QPushButton::clicked, this, &Hyundai_decode::on_buttonEngineSpeed_clicked);
    connect(ui->buttonWspeedFL, &QPushButton::clicked, this, &Hyundai_decode::on_buttonWspeedFL_clicked);
    connect(ui->buttonWspeedFR, &QPushButton::clicked, this, &Hyundai_decode::on_buttonWspeedFR_clicked);
    connect(ui->buttonWspeedRL, &QPushButton::clicked, this, &Hyundai_decode::on_buttonWspeedRL_clicked);
    connect(ui->buttonWspeedRR, &QPushButton::clicked, this, &Hyundai_decode::on_buttonWspeedRR_clicked);

    // Initialize the timer for saving data
    saveTimer = new QTimer(this);
    connect(saveTimer, &QTimer::timeout, this, &Hyundai_decode::saveDataContinuously);

    // Connect start and stop buttons
    connect(ui->buttonSaveStart, &QPushButton::clicked, this, &Hyundai_decode::on_buttonSaveStart_clicked);
    connect(ui->buttonSaveStop, &QPushButton::clicked, this, &Hyundai_decode::on_buttonSaveStop_clicked);
}


void Hyundai_decode::updateTable(const QList<DecodeFrame>& messages)
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
void Hyundai_decode::on_buttonReturn_2_clicked()
{
    Hynndai *hy;
    hide();
    hy = new Hynndai(this);
    hy->show();
    if (_serialPort != nullptr && _serialPort->isOpen()) {
        _serialPort->close();
        qDebug() << "Port Disconnected: COM port has been disconnected.";
    }
    ui->cmbPorts->clear();
}


void Hyundai_decode::on_buttonHome_2_clicked()
{
    MainWindow *mw;
    hide();
    mw = new MainWindow(this);
    mw->show();
    if (_serialPort != nullptr && _serialPort->isOpen()) {
        _serialPort->close();
        qDebug() << "Port Disconnected: COM port has been disconnected.";
    }
    ui->cmbPorts->clear();
}


void Hyundai_decode::on_btnPortsInfo_clicked()
{
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->cmbPorts->addItems(stringPorts);
}

void Hyundai_decode::loadPorts()
{
    foreach (auto &port, QSerialPortInfo::availablePorts() ) {
        ui->cmbPorts->addItem(port.portName());
    }
}

void Hyundai_decode::on_buttonOpen_2_clicked()
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
        QByteArray dataToSend = "4";
        _serialPort->write(dataToSend);

        if (_serialPort->waitForBytesWritten(1000))
        {
            qDebug() << "Data Sent: The string has been sent to the serial port.";
            connect(_serialPort, &QSerialPort::readyRead, this, &Hyundai_decode::handleSerialData);
        }
        else
        {
            qDebug() << "Write Error: Failed to send string.";
        }

    } else {
        QMessageBox::critical(this,"Port Error","Unable to open specified port...");
    }
}

void Hyundai_decode::handleSerialData() {
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

void Hyundai_decode::updateTableValue(const QString &specification, const QString &rawData, const QString &lastValue) {
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

void Hyundai_decode::on_buttonVehicleSpeed_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showVehicleSpeedChart();
    }
}

void Hyundai_decode::on_buttonEngineSpeed_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showEngineSpeedChart();
    }
}


void Hyundai_decode::on_buttonWspeedRL_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedRLChart();
    }
}


void Hyundai_decode::on_buttonWspeedFL_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedFLChart();
    }
}


void Hyundai_decode::on_buttonWspeedFR_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedFRChart();
    }
}


void Hyundai_decode::on_buttonWspeedRR_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->showWheelSpeedRRChart();
    }
}
void Hyundai_decode::on_buttonSaveStart_clicked()
{
    if (!saveTimer->isActive()) {
        saveTimer->start(1000);  // Save data every 1 second (adjust interval as needed)
        QMessageBox::information(this, "Auto Save Started", "Data saving started automatically.");
    }
}
void Hyundai_decode::saveDataContinuously() {
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

void Hyundai_decode::on_buttonSaveStop_clicked()
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

void Hyundai_decode::saveDataToFile(const QString &filePath) {
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


Hyundai_decode::~Hyundai_decode()
{
    delete ui;
}

void Hyundai_decode::on_pushButton_clicked()
{

}

