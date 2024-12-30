#include "toyota_decode.h"
#include "ui_toyota_decode.h"
#include "mainwindow.h"
#include "toyota.h"
#include <QVBoxLayout>

Toyota_decode::Toyota_decode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Toyota_decode)
{
    ui->setupUi(this);
    this->setFixedSize(750,480);


    ui->tableWidgetDecode->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetDecode->verticalHeader()->setVisible(true);
    ui->tableWidgetDecode->setColumnCount(5);
    ui->tableWidgetDecode->setRowCount(9);
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
                                {"0x17C", "Engine speed", "RPM", " ", " "},
                                {"0x309", "Vehicle speed", "Km/h", " ", " "},
                                {"0x1D0", "Wheel speed (FL)", "Km/h", " ", " "},
                                {"0x1D0", "Wheel speed (RL)", "Km/h", " ", " "},
                                {"0x1D0", "Wheel speed (FR)", "Km/h", " ", " "},
                                {"0x1D0", "Wheel speed (RR)", "Km/h", " ", " "},
                                {"0x294", "Right turn switch", "ON/OFF", " ", " "},
                                {"0x294 ", "Left turn switch", "ON/OFF", " ", " "},
                                {"0x294 ", "Hazard", "ON/OFF", " ", " "},
                                {"0x294", "Wiper speed", "", " ", " "},

                                };
    updateTable(infor);

    // Initialize the GraphWindow (initially hidden)
    graphWindow = new graphwindow(this);

    // Connect buttonVehicleSpeed to show the GraphWindow and start plotting
    connect(ui->buttonVehicleSpeed, &QPushButton::clicked, this, &Toyota_decode::on_buttonVehicleSpeed_clicked);

    // Initialize the timer for saving data
    saveTimer = new QTimer(this);
    connect(saveTimer, &QTimer::timeout, this, &Toyota_decode::saveDataContinuously);

    // Connect start and stop buttons
    connect(ui->buttonSaveStart, &QPushButton::clicked, this, &Toyota_decode::on_buttonSaveStart_clicked);
    connect(ui->buttonSaveStop, &QPushButton::clicked, this, &Toyota_decode::on_buttonSaveStop_clicked);
}


void Toyota_decode::updateTable(const QList<DecodeFrame>& messages)
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
void Toyota_decode::on_buttonReturn_2_clicked()
{
    Toyota *tyt;
    hide();
    tyt=new Toyota(this);
    tyt->show();
}


void Toyota_decode::on_buttonHome_2_clicked()
{
    MainWindow *md ;
    hide();
    md = new MainWindow(this);
    md->show();
}


void Toyota_decode::on_btnPortsInfo_clicked()
{
    if (_serialPort != nullptr && _serialPort->isOpen()) {
        _serialPort->close();
        QMessageBox::information(this, "Port Disconnected", "COM port has been disconnected.");
    }
    ui->cmbPorts->clear();
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->cmbPorts->addItems(stringPorts);
}

void Toyota_decode::loadPorts()
{
    foreach (auto &port, QSerialPortInfo::availablePorts() ) {
        ui->cmbPorts->addItem(port.portName());
    }
}

void Toyota_decode::on_buttonOpen_2_clicked()
{
    if(_serialPort != nullptr)
    {
        _serialPort->close();
        delete _serialPort;
    }
    _serialPort = new QSerialPort(this);
    _serialPort->setPortName(ui->cmbPorts->currentText());
    _serialPort->setBaudRate(QSerialPort::Baud9600);
    _serialPort->setDataBits((QSerialPort::Data8));
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);
    if(_serialPort->open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this,"Result","Port opened Successfully");

    }else{
        QMessageBox::critical(this,"Port Error","Unable to open specified port...");
    }
}

void Toyota_decode::on_btnCOMbps_clicked()
{
    // Check if _serialPort is initialized and open
    if (_serialPort == nullptr || !_serialPort->isOpen()) {
        QMessageBox::warning(this, "Error", "Serial port is not open. Please open the port first.");
        return;
    }

    // Retrieve the selected baud rate from cmbCOMBaudRate
    bool ok;
    qint32 baudRate = ui->cmbCOMBaudRate->currentText().toInt(&ok);

    // Check if the baud rate conversion was successful
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid baud rate selected.");
        return;
    }

    // Set the baud rate for the serial port
    if (_serialPort->setBaudRate(baudRate)) {
        QMessageBox::information(this, "Baud Rate Set", "Baud rate successfully set to " + QString::number(baudRate));
        connect(_serialPort, &QSerialPort::readyRead, this, &Toyota_decode::handleSerialData);
    } else {
        QMessageBox::critical(this, "Error", "Failed to set baud rate. Please try again.");
    }

}

void Toyota_decode::handleSerialData() {
    static QByteArray buffer;
    buffer.append(_serialPort->readAll());

    int newlineIndex = buffer.indexOf('\n');
    while (newlineIndex != -1) {
        QByteArray line = buffer.left(newlineIndex).trimmed();
        buffer.remove(0, newlineIndex + 1);

        QList<QByteArray> messageParts = line.split(':');
        if (messageParts.size() == 2) {
            QString specification = messageParts[0].trimmed();
            QString value = messageParts[1].trimmed();

            if (specification == "Vehicle speed" && graphWindow->isVisible()) {
                graphWindow->updateVehicleSpeedPlot(value.toDouble());  // Update the plot in the graph window
            }

            updateTableValue(specification, value);
        }
        newlineIndex = buffer.indexOf('\n');
    }
}

void Toyota_decode::updateTableValue(const QString &specification, const QString &value)
{
    // Find the row in tableWidgetDecode based on the specification and update the value in the fourth column
    for (int row = 0; row < ui->tableWidgetDecode->rowCount(); ++row) {
        QTableWidgetItem *item = ui->tableWidgetDecode->item(row, 1);  // Column 1 for "Specification"
        if (item && item->text() == specification) {
            QTableWidgetItem *valueItem = new QTableWidgetItem(value);  // Create a new QTableWidgetItem for the value
            valueItem->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetDecode->setItem(row, 3, valueItem);  // Update column 3 (Value)
            return;
        }
    }
    qDebug() << "Specification not recognized:" << specification;
}

void Toyota_decode::on_buttonVehicleSpeed_clicked()
{
    if (!graphWindow->isVisible()) {
        graphWindow->show();  // Show the graph window
    }
}


void Toyota_decode::on_buttonSaveStart_clicked()
{
    if (!saveTimer->isActive()) {
        saveTimer->start(1000);  // Save data every 1 second (adjust interval as needed)
        QMessageBox::information(this, "Auto Save Started", "Data saving started automatically.");
    }
}
void Toyota_decode::saveDataContinuously() {
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

void Toyota_decode::on_buttonSaveStop_clicked()
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

void Toyota_decode::saveDataToFile(const QString &filePath) {
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


Toyota_decode::~Toyota_decode()
{
    delete ui;
}
