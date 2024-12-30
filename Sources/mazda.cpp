#include "mazda.h"
#include "ui_mazda.h"
#include "mazda_monitor.h"
#include "mainwindow.h"
#include "mazda_decode.h"
#include "mazda_rtr.h"
#include "mazda_signal.h"

MainWindow *Mwd;
Mazda_monitor *Mzdnitor;
Mazda_Decode * Mzddecode;
Mazda_RTR *rtr;
mazda_signal *Mzdsignal;
Mazda::Mazda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mazda)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMaximizeButtonHint| Qt::WindowCloseButtonHint |Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    this->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));

    this->setFixedSize(705,410);

}
Mazda::~Mazda()
{
    delete ui;
}

void Mazda::startBackgroundProcess(const QString &command)
{
    QProcess *process = new QProcess(this);
    process->start("/bin/sh", QStringList() << "-c" << "sudo " + command + " &");

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start background process.";
    } else {
        qDebug() << "Background process started successfully.";
    }
}



void Mazda::on_buttonHome_clicked()
{
    hide();
    Mwd = new MainWindow(this);
    Mwd->show();
    startBackgroundProcess("ip link set dev can0 down");

}

void Mazda::on_pushButtonMonitor_clicked()
{
    hide();
    Mzdnitor = new Mazda_monitor(this);
    Mzdnitor->show();
}


void Mazda::on_pushButton_6_clicked()
{
    hide();
    Mzddecode = new Mazda_Decode(this);
    Mzddecode->show();
}


void Mazda::on_pushButton_8_clicked()
{
    hide();
    rtr = new Mazda_RTR(this);
    rtr->show();
}


void Mazda::on_pushButton_7_clicked()
{
    hide();
    Mzdsignal = new mazda_signal(this);
    Mzdsignal->show();
}

