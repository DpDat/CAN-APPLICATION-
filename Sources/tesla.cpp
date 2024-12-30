#include "tesla.h"
#include "ui_tesla.h"
#include "mainwindow.h"
#include "tesla_monitor.h"
#include "tesla_decode.h"
#include "tesla_rtr.h"

Tesla::Tesla(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Tesla)
{
    ui->setupUi(this);
}

Tesla::~Tesla()
{
    delete ui;
}

void Tesla::on_buttonHome_clicked()
{
    hide();
    MainWindow *mw;
    mw=new MainWindow(this);
    mw->show();
}


void Tesla::on_pushButtonMonitor_clicked()
{
    hide();
    Tesla_monitor *tlm;
    tlm = new Tesla_monitor(this);
    tlm->show();
}


void Tesla::on_pushButton_6_clicked()
{
    hide();
    Tesla_decode *tld;
    tld = new Tesla_decode(this);
    tld->show();
}


void Tesla::on_pushButton_8_clicked()
{
    hide();
    Tesla_rtr *tlr;
    tlr = new Tesla_rtr(this);
    tlr->show();
}

