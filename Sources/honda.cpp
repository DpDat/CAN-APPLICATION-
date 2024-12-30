#include "honda.h"

Honda::Honda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Honda)
{
    ui->setupUi(this);
    this->setFixedSize(705, 410);
}

Honda::~Honda()
{
    delete ui;
}

void Honda::startBackgroundProcess(const QString &command)
{
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::finished, process, &QObject::deleteLater);

    process->start("/bin/sh", QStringList() << "-c" << "sudo " + command + " &");

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start background process.";
    } else {
        qDebug() << "Background process started successfully.";
    }
}

void Honda::on_buttonHome_clicked()
{
    QScopedPointer<MainWindow> Mwd(new MainWindow(this));
    hide();
    Mwd->show();
    startBackgroundProcess("ip link set dev can0 down");
}

// Tương tự cho các hàm khác
