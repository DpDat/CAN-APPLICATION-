#include "hynndai.h"
#include "ui_hynndai.h"
#include "mainwindow.h"
#include "hyundai_monitor.h"
#include "hyundai_decode.h"
#include "hyundai_rtr.h"


Hynndai::Hynndai(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Hynndai)
{
    ui->setupUi(this);
}

Hynndai::~Hynndai()
{
    delete ui;
}

void Hynndai::on_buttonHome_clicked()
{
    hide();
    MainWindow *mw ;
    mw = new MainWindow(this);
    mw->show();
}


void Hynndai::on_pushButtonMonitor_clicked()
{
    hide();
    Hyundai_monitor *hym ;
    hym = new Hyundai_monitor;
    hym->show();

}


void Hynndai::on_pushButton_6_clicked()
{
    hide();
    Hyundai_decode *hyc;
    hyc = new Hyundai_decode(this);
    hyc->show();
}


void Hynndai::on_pushButton_8_clicked()
{
    hide();
    Hyundai_rtr *hyr;
    hyr =new Hyundai_rtr(this);
    hyr->show();
}

