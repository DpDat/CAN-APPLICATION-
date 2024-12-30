#include "toyota_monitor.h"
#include "ui_toyota_monitor.h"
#include "toyota.h"
#include "mainwindow.h"

Toyota_monitor::Toyota_monitor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Toyota_monitor)
{
    ui->setupUi(this);
    this->setFixedSize(880,560);


    ui->tableWidgetData->verticalHeader()->setVisible(true);
    ui->tableWidgetData->setColumnCount(5);
    ui->tableWidgetData->setRowCount(1);

    ui->tableWidgetData->setColumnWidth(0,105);
    ui->tableWidgetData->setColumnWidth(1,105);
    ui->tableWidgetData->setColumnWidth(2,105);
    ui->tableWidgetData->setColumnWidth(3,105);
    ui->tableWidgetData->setColumnWidth(4,200);

    ui->tableWidgetData->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Make the table read-only

    ui->tableWidgetData->setStyleSheet(
        "QTableWidget { border: 1px solid blue; } QHeaderView::section { background-color: gray; } QTableWidget::item { background-color: lightgray; }"
        "QTableWidget::item { "
        "border-top: 0.5px solid black; "
        "border-right: 0.5px solid black; "
        "border-bottom: 0.5px solid black; "
        "border-left: 0.5px solid black; "
        "}"
        );

    // example data
    QList<CANMessage> exampleMessages = {
                                         {"Received", "1.0", "0x123", "8", "AA BB CC DD EE FF 00 11"},
                                         };
    updateTable(exampleMessages);
}


void Toyota_monitor::updateTable(const QList<CANMessage>& messages)
{
    ui->tableWidgetData->clearContents();
    int row = 0;
    QFont customFont("Arial", 10, QFont::Bold);

    for (const CANMessage &msg : messages) {
        if (row >= ui->tableWidgetData->rowCount())
            break;

        QTableWidgetItem *directionItem = new QTableWidgetItem(msg.direction);
        directionItem->setFont(customFont);
        directionItem->setForeground(Qt::blue);
        directionItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(row, 0, directionItem);

        QTableWidgetItem *timeScaleItem = new QTableWidgetItem(msg.timeScale);
        timeScaleItem->setFont(customFont);
        timeScaleItem->setForeground(Qt::darkGreen);
        timeScaleItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(row, 1, timeScaleItem);

        QTableWidgetItem *canIDItem = new QTableWidgetItem(msg.canID);
        canIDItem->setFont(customFont);
        canIDItem->setForeground(Qt::red);
        canIDItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(row, 2, canIDItem);

        QTableWidgetItem *dlcItem = new QTableWidgetItem(msg.dlc);
        dlcItem->setFont(customFont);
        dlcItem->setForeground(Qt::darkBlue);
        dlcItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(row, 3, dlcItem);

        QTableWidgetItem *dataItem = new QTableWidgetItem(msg.data);
        dataItem->setFont(customFont);
        dataItem->setForeground(Qt::darkMagenta);
        dataItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(row, 4, dataItem);

        row++;
    }
}



void Toyota_monitor::startBackgroundProcess(const QString &command)
{
    QProcess *process = new QProcess(this);
    process->start("/bin/sh", QStringList() << "-c" << "sudo " + command + " &");

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start background process.";
    } else {
        qDebug() << "Background process started successfully.";
    }
}


void Toyota_monitor::on_buttonHome_clicked()
{
    MainWindow *Mwd;
    hide();
    Mwd = new MainWindow(this);
    Mwd->show();
}

void Toyota_monitor::on_buttonReturn_clicked()
{
    hide();
    Toyota *tyt;
    tyt = new Toyota(this);
    tyt->show();
}

void Toyota_monitor::on_btCANInterface_clicked()
{
    // Clear the combo box before adding new items
    ui->cmbCANInterface->clear();

    QString errorString;
    // Retrieve available devices for the "socketcan" plugin (or other CAN plugin you're using)
    const QList<QCanBusDeviceInfo> devices = QCanBus::instance()->availableDevices(QStringLiteral("socketcan"), &errorString);

    // Check if there was an error during the device search
    if (!errorString.isEmpty()) {
        qDebug() << "Error retrieving CAN devices:" << errorString;
        QMessageBox::critical(this, "CAN Device Error", "Failed to retrieve CAN devices: " + errorString);
        return;
    }

    // Add each available device to cmbCANDevices
    for (const QCanBusDeviceInfo &device : devices) {
        ui->cmbCANInterface->addItem(device.name());  // device.name() returns something like "can0", "slcan0", etc.
    }

    // Display a message if no CAN devices are found
    if (devices.isEmpty()) {
        QMessageBox::information(this, "No CAN Devices", "No available CAN devices were found.");
    }
}


void Toyota_monitor::Delay(int milliseconds) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}


void Toyota_monitor::on_btCANbps_clicked()
{
    int bitrate = ui->cmbCANBaudRate->currentIndex();
    QString selectedInterface = ui->cmbCANInterface->currentText();
    int canBaudRate = ui->cmbCANBaudRate->currentText().toInt();  // Assumes cmbCANBaudRate contains common CAN baud rates

    if (canDevice) {
        canDevice->disconnectDevice();
        delete canDevice;
        canDevice = nullptr;
    }

    QString errorString;
    canDevice = QCanBus::instance()->createDevice("socketcan", selectedInterface, &errorString);

    if (!canDevice) {
        QMessageBox::critical(this, "CAN Device Error", "Failed to create CAN device: " + errorString);
        return;
    }

    // Skip bitrate setting for vcan interfaces
    switch(bitrate){
    case 0 :
        QMessageBox::critical(this, "CAN Device Error", "Failed to create CAN device: " + errorString);
        return;
    case 1 :
        startBackgroundProcess("ip link set dev can0 down");
        qDebug() << "shut down can0"  ;
        Delay(500);
        startBackgroundProcess("ip link set dev can0 type can bitrate 125000 && sudo ip link set dev can0 up");
        qDebug() << "set and turn up can0" ;
        break ;
    case 2 :
        startBackgroundProcess("ip link set dev can0 down");
        Delay(500);
        startBackgroundProcess("ip link set dev can0 type can bitrate 250000 && sudo ip link set dev can0 up");
        break ;
    case 3 :
        startBackgroundProcess("ip link set dev can0 down");
        Delay(500);
        startBackgroundProcess("ip link set dev can0 type can bitrate 500000 && sudo ip link set dev can0 up");
        break ;
    case 4 :
        startBackgroundProcess("ip link set dev can0 down");
        Delay(500);
        startBackgroundProcess("ip link set dev can0 type can bitrate 1000000 && sudo ip link set dev can0 up");
        break ;
    case 5 :
        startBackgroundProcess("ip link set dev can0 down");
        Delay(500);
        startBackgroundProcess("ip link set dev can0 type can bitrate 2000000 && sudo ip link set dev can0 up");
        break ;
    }

    if (canDevice->connectDevice()) {
        QMessageBox::information(this, "CAN Connected", "Connected to CAN interface " + selectedInterface + " at baud rate " + QString::number(canBaudRate) + " bps.");

        // Connect the framesReceived signal to handle incoming CAN messages
        connect(canDevice, &QCanBusDevice::framesReceived, this, &Toyota_monitor::handleReceivedMessage);
    } else {
        QMessageBox::critical(this, "Connection Error", "Failed to connect to CAN device: " + canDevice->errorString());
        delete canDevice;
        canDevice = nullptr;
    }
}


void Toyota_monitor::handleReceivedMessage()
{
    while (canDevice && canDevice->framesAvailable()) {
        QCanBusFrame frame = canDevice->readFrame();

        QString direction = "Received";
        QString timeScale = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        QString canID = QString("0x%1").arg(frame.frameId(), 0, 16).toUpper();
        QString dlc = QString::number(frame.payload().size());
        QString data = frame.payload().toHex(' ').toUpper();

        // Add a new row at the bottom of the table
        int newRow = ui->tableWidgetData->rowCount();
        ui->tableWidgetData->insertRow(newRow);

        QTableWidgetItem *directionItem = new QTableWidgetItem(direction);
        directionItem->setForeground(Qt::blue);
        directionItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(newRow, 0, directionItem);

        QTableWidgetItem *timeScaleItem = new QTableWidgetItem(timeScale);
        timeScaleItem->setForeground(Qt::darkGreen);
        timeScaleItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(newRow, 1, timeScaleItem);

        QTableWidgetItem *canIDItem = new QTableWidgetItem(canID);
        canIDItem->setForeground(Qt::red);
        canIDItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(newRow, 2, canIDItem);

        QTableWidgetItem *dlcItem = new QTableWidgetItem(dlc);
        dlcItem->setForeground(Qt::darkBlue);
        dlcItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(newRow, 3, dlcItem);

        QTableWidgetItem *dataItem = new QTableWidgetItem(data);
        dataItem->setForeground(Qt::darkMagenta);
        dataItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetData->setItem(newRow, 4, dataItem);

        // Scroll to the new row to make it visible
        ui->tableWidgetData->scrollToItem(directionItem);
    }
}


void Toyota_monitor::on_buttonStop_clicked()
{
    // Check if the CAN device is connected
    if (canDevice) {
        // Disconnect the CAN device
        canDevice->disconnectDevice();
        delete canDevice;  // Clean up the device
        canDevice = nullptr;  // Reset the pointer

        // Inform the user
        QMessageBox::information(this, "CAN Stopped", "CAN message receiving has been stopped.");
    } else {
        QMessageBox::warning(this, "Error", "No CAN device is currently connected.");
    }
}


void Toyota_monitor::on_btCANFilter_clicked()
{
    bool ok;
    uint canId = ui->IDFilter->text().toUInt(&ok, 16); // Read as hex (e.g., 0x444)

    if (!ok) {
        QMessageBox::warning(this, "Invalid CAN ID", "Please enter a valid hexadecimal CAN ID.");
        return;
    }
    // Create a filter based on the entered CAN ID
    QCanBusDevice::Filter filter;
    QList<QCanBusDevice::Filter> filterList;

    filter.frameId = canId;
    filter.frameIdMask = 0x7FFu; // Standard 11-bit mask
    filter.format = QCanBusDevice::Filter::MatchBaseAndExtendedFormat;
    filter.type = QCanBusFrame::DataFrame; // Filter only DataFrames
    filterList.append(filter);

    // Apply the filter to the device
    if (canDevice) {
        canDevice->setConfigurationParameter(QCanBusDevice::RawFilterKey, QVariant::fromValue(filterList));
        QMessageBox::information(this, "CAN Filter Applied", "Filter applied for CAN ID: " + QString::number(canId, 16).toUpper());
    } else {
        QMessageBox::warning(this, "Error", "No CAN device connected.");
    }
}

void Toyota_monitor::on_buttonSave_clicked()
{

    // Ask the user for a file name using an input dialog
    bool ok;
    QString baseFileName = QInputDialog::getText(this, "File Name", "Enter file name:", QLineEdit::Normal, "", &ok);

    // Check if the user clicked OK and provided a file name
    if (!ok || baseFileName.isEmpty()) {
        return;  // Exit if no file name was entered
    }

    // Open a file dialog to select the save directory
    QString directory = QFileDialog::getExistingDirectory(this, "Select Directory");
    if (directory.isEmpty()) {
        return;  // Exit if no directory was selected
    }

    // Combine directory and filename, adding .csv extension
    QString fileName = directory + "/" + baseFileName + ".csv";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Unable to open file", "Could not open file for writing.");
        return;
    }

    QTextStream out(&file);

    // Write the header row
    out << "Direction,Time Scale,CAN ID,DLC,Data\n";

    // Write the data rows
    for (int row = 0; row < ui->tableWidgetData->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->tableWidgetData->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidgetData->item(row, col);
            if (item) {
                rowData << item->text();
            } else {
                rowData << "";  // Add an empty string if the item is null
            }
        }
        out << rowData.join(",") << "\n";  // Join row data with commas for CSV format
    }

    file.close();

    QMessageBox::information(this, "Save Successful", "CAN data has been saved as " + fileName);

}

void Toyota_monitor::on_buttonOpenFile_clicked()
{
    // Open a file dialog to select the CSV file
    QString fileName = QFileDialog::getOpenFileName(this, "Open CAN Data File", "", "CSV Files (*.csv);;All Files (*)");
    if (fileName.isEmpty()) {
        return;  // If no file is selected, exit the function
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Unable to open file", "Could not open the selected file for reading.");
        return;
    }

    QTextStream in(&file);

    // Clear existing data in the table
    ui->tableWidgetData->setRowCount(0);

    // Skip the header row (if present) and read data rows
    bool isHeader = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (isHeader) {
            isHeader = false;  // Skip the header line
            continue;
        }

        QStringList rowData = line.split(',');  // Split line by commas for CSV format
        if (rowData.size() < ui->tableWidgetData->columnCount()) {
            continue;  // Skip if the row data doesn't match the table's column count
        }

        // Add a new row to the table
        int newRow = ui->tableWidgetData->rowCount();
        ui->tableWidgetData->insertRow(newRow);

        // Populate the row with data from the file
        for (int col = 0; col < rowData.size() && col < ui->tableWidgetData->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(rowData[col].trimmed());
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetData->setItem(newRow, col, item);
        }
    }

    file.close();
    QMessageBox::information(this, "Open Successful", "CAN data has been loaded from " + fileName);
}


void Toyota_monitor::startPulseview()
{
    QProcess *process = new QProcess();
    process->setProgram("pulseview");

    // �?c l?i
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





void Toyota_monitor::on_pushButton_clicked()
{
    startPulseview();
}



Toyota_monitor::~Toyota_monitor()
{
    delete ui;
}
