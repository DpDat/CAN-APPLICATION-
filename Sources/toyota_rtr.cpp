#include "toyota_rtr.h"
#include "ui_toyota_rtr.h"
#include "toyota.h"
#include "mainwindow.h"
#include <QComboBox>
#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>
#include <QMap>

Toyota_rtr::Toyota_rtr(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Toyota_rtr)
{
    ui->setupUi(this);
    this->setFixedSize(750, 600);

    ui->tableWidgetRequest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetRequest->setColumnCount(4);
    ui->tableWidgetRequest->setRowCount(1);

    ui->tableWidgetResponse->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetResponse->setColumnCount(3);
    ui->tableWidgetResponse->setRowCount(1);


    // Initialize transmit timer
    transmitTimer = new QTimer(this);
    connect(transmitTimer, &QTimer::timeout, this, &Toyota_rtr::sendCANFrame);

    // example data
    QList<CANMessageTransmit> exampleMessages = {
                                                 {"Transmit", "0x123", "8", "AA BB CC DD EE FF 00 11"},

                                                 };
    updateTable(exampleMessages);

    QList<CANMessageReceive> exampleMessagesReive = {
                                                     {"7E8", "8", "04 41 0C 0A F8 00 00 00"},

                                                     };
    updateTableReceive(exampleMessagesReive);

}

void Toyota_rtr::updateTable(const QList<CANMessageTransmit>& messages)
{
    ui->tableWidgetRequest->setRowCount(ui->tableWidgetRequest->rowCount());
    int row = 0;
    QFont customFont("Arial", 10, QFont::Bold);

    for (const CANMessageTransmit &msg : messages) {
        if (row >= ui->tableWidgetRequest->rowCount())
            break;

        QTableWidgetItem *directionItem = new QTableWidgetItem(msg.direction);
        directionItem->setForeground(Qt::blue);
        directionItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetRequest->setItem(row, 0, directionItem);


        QTableWidgetItem *canIDItem = new QTableWidgetItem(msg.canID);
        canIDItem->setFont(customFont);
        canIDItem->setForeground(Qt::red);
        canIDItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetRequest->setItem(row, 1, canIDItem);

        QTableWidgetItem *dlcItem = new QTableWidgetItem(msg.dlc);
        dlcItem->setFont(customFont);
        dlcItem->setForeground(Qt::darkBlue);
        dlcItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetRequest->setItem(row, 2, dlcItem);

        QTableWidgetItem *dataItem = new QTableWidgetItem(msg.data);
        dataItem->setFont(customFont);
        dataItem->setForeground(Qt::darkMagenta);
        dataItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetRequest->setItem(row, 3,dataItem);


        row++;
    }
}

void Toyota_rtr::updateTableReceive(const QList<CANMessageReceive>& messages)
{
    ui->tableWidgetResponse->setRowCount(ui->tableWidgetResponse->rowCount());
    int row = 0;
    QFont customFont("Arial", 10, QFont::Bold);

    for (const CANMessageReceive &msg : messages) {
        if (row >= ui->tableWidgetResponse->rowCount())
            break;

        QTableWidgetItem *canIDItem = new QTableWidgetItem(msg.CanID);
        canIDItem->setFont(customFont);
        canIDItem->setForeground(Qt::red);
        canIDItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetResponse->setItem(row, 0, canIDItem);

        QTableWidgetItem *dlcItem = new QTableWidgetItem(msg.DLC);
        dlcItem->setFont(customFont);
        dlcItem->setForeground(Qt::darkBlue);
        dlcItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetResponse->setItem(row, 1, dlcItem);

        QTableWidgetItem *dataItem = new QTableWidgetItem(msg.DATA);
        dataItem->setFont(customFont);
        dataItem->setForeground(Qt::darkMagenta);
        dataItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetResponse->setItem(row, 2,dataItem);
        row++;
    }
}

void Toyota_rtr::startBackgroundProcess(const QString &command)
{
    QProcess *process = new QProcess(this);
    process->start("/bin/sh", QStringList() << "-c" << "sudo " + command + " &");

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start background process.";
    } else {
        qDebug() << "Background process started successfully.";
    }
}



void Toyota_rtr::on_buttonReturn_clicked()
{
    hide();
    Toyota *tyt;
    tyt = new Toyota(this);
    tyt->show();
}


void Toyota_rtr::on_btCANInterface_clicked()
{
    // Clear the combo box before adding new items
    ui->cmbCANInterface->clear();

    QString errorString;

    // Retrieve the list of available CAN interfaces
    const QList<QCanBusDeviceInfo> devices = QCanBus::instance()->availableDevices(QStringLiteral("socketcan"), &errorString);

    // Check for errors when querying devices
    if (!errorString.isEmpty()) {
        qDebug() << "Error while querying CAN devices:" << errorString;
        QMessageBox::critical(this, "CAN Device Error", "Cannot list CAN devices: " + errorString);
        return;
    }

    // Check if the list of devices is empty
    if (devices.isEmpty()) {
        QMessageBox::information(this, "No CAN Device", "No available CAN devices found.");
        return;
    }

    bool can0Found = false;

    // Add interfaces to the combo box
    for (const QCanBusDeviceInfo &device : devices) {
        ui->cmbCANInterface->addItem(device.name());
        if (device.name() == "can0") {
            can0Found = true;
        }
    }

    // If can0 is not found, stop
    if (!can0Found) {
        QMessageBox::information(this, "CAN Interface", "The 'can0' interface is not available.");
        return;
    }

    ui->cmbCANInterface->setCurrentText("can0");

    // Connect to the CAN device
    canDevice = QCanBus::instance()->createDevice("socketcan", "can0", &errorString);
    if (!canDevice) {
        QMessageBox::critical(this, "CAN Device Error", "Cannot connect to CAN: " + errorString);
        return;
    }

    if (canDevice->connectDevice()) {
        QMessageBox::information(this, "CAN Device", "Successfully connected to the 'can0' interface.");
    } else {
        QMessageBox::critical(this, "Connection Error", "Cannot connect to the CAN device: " + canDevice->errorString());
        delete canDevice;
        canDevice = nullptr;
    }
}

void Toyota_rtr::on_BtnSetRequest_clicked()
{
    QString selectedRequest = ui->comboBoxRequest->currentText().trimmed();  // Trim any extra whitespace
    qDebug() << "Selected request type:" << selectedRequest;
    CANMessageTransmit message;

    if (selectedRequest == "Vehicle Speed") {
        message = {"Transmit", "0x7DF", "8", "02 01 0D 00 00 00 00 00"};
    } else if (selectedRequest == "Engine Speed") {
        message = {"Transmit", "0x7DF", "8", "02 01 0C 00 00 00 00 00"};
    } else if (selectedRequest == "Diagnostic") {
        message = {"Transmit","0x7DF", "8", "01 03 00 00 00 00 00 00"};
    }else if (selectedRequest == "Engine coolant temperature") {
        message = {"Transmit","0x7DF", "8", "02 01 05 00 00 00 00 00"};
    } else if (selectedRequest == "Engine load") {
        message = {"Transmit", "0x7DF", "8", "02 01 04 00 00 00 00 00"};
    } else if (selectedRequest == "Fuel pressure") {
        message = {"Transmit", "0x7DF", "8", "02 01 0A 00 00 00 00 00"};
    } else if (selectedRequest == "Intake air temperature") {
        message = {"Transmit", "0x7DF", "8", "02 01 0F 00 00 00 00 00"};
    } else if (selectedRequest == "air flow rate") {
        message = {"Transmit", "0x7DF", "8", "02 01 10 00 00 00 00 00"};
    } else if (selectedRequest == "Throttle position") {
        message = {"Transmit", "0x7DF", "8", "02 01 11 00 00 00 00 00"};
    } else if (selectedRequest == "Run time since engine start") {
        message = {"Transmit", "0x7DF", "8", "02 01 1F 00 00 00 00 00"};
    } else {
        qDebug() << "Unknown request type";
        return;
    }

    // Update table with the selected frame
    updateTable({message});

    // Set the message to send in the timer loop
    currentCANMessage = message;
}

void Toyota_rtr::sendCANFrame()
{
    if (canDevice && canDevice->state() == QCanBusDevice::ConnectedState) {
        QCanBusFrame frame;

        // Set Frame ID and Data Payload
        frame.setFrameId(currentCANMessage.canID.toUInt(nullptr, 16));
        frame.setPayload(QByteArray::fromHex(currentCANMessage.data.remove(' ').toLatin1()));

        // Send Frame
        if (canDevice->writeFrame(frame)) {
            qDebug() << "CAN frame sent successfully!";

            // Dynamically add the transmitted frame to the table
            QFont customFont("Arial", 10, QFont::Bold);
            int newRow = ui->tableWidgetRequest->rowCount();
            ui->tableWidgetRequest->insertRow(newRow);

            // Direction: Transmit
            QTableWidgetItem *directionItem = new QTableWidgetItem("Transmit");
            directionItem->setFont(customFont);
            directionItem->setForeground(Qt::blue);
            directionItem->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetRequest->setItem(newRow, 0, directionItem);

            // CAN ID
            QTableWidgetItem *canIDItem = new QTableWidgetItem(currentCANMessage.canID);
            canIDItem->setFont(customFont);
            canIDItem->setForeground(Qt::red);
            canIDItem->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetRequest->setItem(newRow, 1, canIDItem);

            // DLC
            QTableWidgetItem *dlcItem = new QTableWidgetItem(currentCANMessage.dlc);
            dlcItem->setFont(customFont);
            dlcItem->setForeground(Qt::darkBlue);
            dlcItem->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetRequest->setItem(newRow, 2, dlcItem);

            // Data
            QTableWidgetItem *dataItem = new QTableWidgetItem(currentCANMessage.data);
            dataItem->setFont(customFont);
            dataItem->setForeground(Qt::darkMagenta);
            dataItem->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetRequest->setItem(newRow, 3, dataItem);

            // Automatically scroll to the newly added row
            ui->tableWidgetRequest->scrollToItem(directionItem);

        } else {
            qDebug() << "Failed to send CAN frame: " << canDevice->errorString();
        }
    } else {
        qDebug() << "CAN device is not connected.";
    }
}

void Toyota_rtr::on_pushButton_clicked(bool checked)
{
    static bool isSending = false;  // Flag to track sending status
    static bool isReceiving = false; // Flag to track receiving status

    if (!isSending && !isReceiving && checked) {
        isSending = true;
        isReceiving = true;
        qDebug() << "Starting CAN frame transmission and reception...";

        while (isSending && isReceiving) {
            sendCANFrame();
            Delay(1000);
            receiveCANFrame();
            Delay(1000);
            // Check if the button was pressed again during the delay to stop sending and receiving
            QCoreApplication::processEvents();
        }
    } else {
        isSending = false;  // Stop the sending process
        isReceiving = false; // Stop the receiving process
        qDebug() << "Stopping CAN frame transmission and reception...";
    }
}

QList<CANMessageReceive> Toyota_rtr::filterCANMessages(const QList<CANMessageReceive>& messages) {
    QList<CANMessageReceive> filteredMessages;

    for (const CANMessageReceive &msg : messages) {
        bool ok;
        uint32_t canID = msg.CanID.toUInt(&ok, 16); // Convert CAN ID to an integer
        if (ok && canID >= 0x7E0 && canID <= 0x7FF) {
            filteredMessages.append(msg); // Add message to the filtered list if it matches
        }
    }

    return filteredMessages; // Return the filtered messages
}

void Toyota_rtr::receiveCANFrame() {
    if (canDevice && canDevice->state() == QCanBusDevice::ConnectedState) {
        while (canDevice->framesAvailable() > 0) {
            QCanBusFrame frame = canDevice->readFrame();  // Read a frame from the CAN device
            qDebug() << "Received frame:" << frame.toString();

            // Extract CAN ID and Data
            CANMessageReceive receivedMessage;
            receivedMessage.CanID = QString::number(frame.frameId(), 16).toUpper();
            receivedMessage.DLC = QString::number(frame.payload().size());
            receivedMessage.DATA = QString(frame.payload().toHex(' ').toUpper());

            // Filter the CAN messages
            QList<CANMessageReceive> receivedMessages = { receivedMessage };
            QList<CANMessageReceive> filteredMessages = filterCANMessages(receivedMessages);

            // Update the response table with filtered messages
            QFont customFont("Arial", 10, QFont::Bold);
            for (const CANMessageReceive& filteredMsg : filteredMessages) {
                int newRow = ui->tableWidgetResponse->rowCount();
                ui->tableWidgetResponse->insertRow(newRow);

                // CAN ID
                QTableWidgetItem *canIDItem = new QTableWidgetItem(filteredMsg.CanID);
                canIDItem->setFont(customFont);
                canIDItem->setForeground(Qt::red);
                canIDItem->setTextAlignment(Qt::AlignCenter);
                ui->tableWidgetResponse->setItem(newRow, 0, canIDItem);

                // DLC
                QTableWidgetItem *dlcItem = new QTableWidgetItem(filteredMsg.DLC);
                dlcItem->setFont(customFont);
                dlcItem->setForeground(Qt::darkBlue);
                dlcItem->setTextAlignment(Qt::AlignCenter);
                ui->tableWidgetResponse->setItem(newRow, 1, dlcItem);

                // Data
                QTableWidgetItem *dataItem = new QTableWidgetItem(filteredMsg.DATA);
                dataItem->setFont(customFont);
                dataItem->setForeground(Qt::darkMagenta);
                dataItem->setTextAlignment(Qt::AlignCenter);
                ui->tableWidgetResponse->setItem(newRow, 2, dataItem);

                // Automatically scroll to the newly added row
                ui->tableWidgetResponse->scrollToItem(canIDItem);
            }
        }
    } else {
        qDebug() << "CAN device is not connected.";
    }
}

void Toyota_rtr::Delay(int milliseconds) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}

void Toyota_rtr::on_pushButton_2_clicked()
{
    int bitrate = ui->Cmbbitrate->currentIndex() ;
    QString errorString;

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
}

void Toyota_rtr::on_buttonSave_clicked()
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
    out << "CAN ID,DLC,Data\n";

    // Write the data rows
    for (int row = 0; row < ui->tableWidgetResponse->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->tableWidgetResponse->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidgetResponse->item(row, col);
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

void Toyota_rtr::on_buttonOpen_clicked()
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
    ui->tableWidgetResponse->setRowCount(0);

    // Skip the header row (if present) and read data rows
    bool isHeader = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (isHeader) {
            isHeader = false;  // Skip the header line
            continue;
        }

        QStringList rowData = line.split(',');  // Split line by commas for CSV format
        if (rowData.size() < ui->tableWidgetResponse->columnCount()) {
            continue;  // Skip if the row data doesn't match the table's column count
        }

        // Add a new row to the table
        int newRow = ui->tableWidgetResponse->rowCount();
        ui->tableWidgetResponse->insertRow(newRow);

        // Populate the row with data from the file
        for (int col = 0; col < rowData.size() && col < ui->tableWidgetResponse->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(rowData[col].trimmed());
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetResponse->setItem(newRow, col, item);
        }
    }

    file.close();
    QMessageBox::information(this, "Open Successful", "CAN data has been loaded from " + fileName);
}




void Toyota_rtr::on_buttonHome_clicked()
{
    hide();
    MainWindow *mw ;
    mw = new MainWindow(this);
    mw->show();
}


Toyota_rtr::~Toyota_rtr()
{
    delete ui;
}
