#include "honda1.h"
#include "ui_honda1.h"
#include "mainwindow.h"
#include "honda_monitor.h"
#include "honda_decode.h"
#include "honda_rtr.h"


//MainWindow *Mwd;

Honda1::Honda1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Honda1)
{
    ui->setupUi(this);
}

Honda1::~Honda1()
{
    delete ui;
}

void Honda1::startBackgroundProcess(const QString &command)
{
    QProcess *process = new QProcess(this);
    process->start("/bin/sh", QStringList() << "-c" << "sudo " + command + " &");

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start background process.";
    } else {
        qDebug() << "Background process started successfully.";
    }
}

void Honda1::on_buttonHome_clicked()
{
    MainWindow *Mwd;
    hide();
    Mwd = new MainWindow(this);
    Mwd->show();
    startBackgroundProcess("ip link set dev can0 down");

}



void Honda1::on_pushButtonMonitor_clicked()
{
    hide();
    Honda_monitor *hdm ;
    hdm = new Honda_monitor(this);
    hdm->show();
}


void Honda1::on_pushButton_6_clicked()
{
    hide();
    Honda_decode *hdc;
    hdc = new Honda_decode(this);
    hdc->show();
}


void Honda1::on_pushButton_8_clicked()
{
    hide();
    Honda_rtr *hdr ;
    hdr = new Honda_rtr(this);
    hdr->show();
}

