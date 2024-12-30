#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mazda.h"
#include "honda1.h"
#include "hynndai.h"
#include "tesla.h"
#include <QFileDialog>
Mazda *md;
Honda1 *hd ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //this->setFixedSize(670,450);

    ui->pushButtonHome->setIcon(QIcon("C:/Users/dell/Documents/Pyside6 and Qt/icons/Home"));
    ui->pushButtonMazda->setIcon(QIcon(":/Assets/mazda-48.ico"));
    ui->pushButtonHonda->setIcon(QIcon(":/Car_logos/honda_logo_icon_248078.ico"));
    ui->pushButtonHyundai->setIcon(QIcon(":/Car_logos/hyundai_logo_icon_248055.ico"));
    ui->pushButtonTesla->setIcon(QIcon(":/Car_logos/tesla_logo_icon_169601.ico"));
    ui->pushButtonDocuments->setIcon(QIcon(":/Assets/documents-48.ico"));
    ui->pushButtonVideo->setIcon(QIcon(":/Assets/video-play-48.ico"));
    ui->pushButtonDevices->setIcon(QIcon(":/Assets/electro-devices-48.ico"));

    ui->pushButtonMazda->setVisible(false);
    ui->pushButtonHonda->setVisible(false);
    ui->pushButtonHyundai->setVisible(false);
    ui->pushButtonTesla->setVisible(false);

    ui->pushButtonDevices->setVisible(false);
    ui->pushButtonDocuments->setVisible(false);
    ui->pushButtonVideo->setVisible(false);

    ui->pushButtonCar->setVisible(true);
    ui->pushButtonHelps->setVisible(true);

    ui->pushButtonCar->move(0,90);
    ui->pushButtonHelps->move(0,120);
    ui->pushButtonDocuments->move(0,150);
    ui->pushButtonVideo->move(0,170);
    ui->pushButtonDevices->move(0,190);


    bool subButtonsVisible_brandCars = false;

    bool subButtonsVisible_Help = false;

    connect(ui->pushButtonCar, &QPushButton::clicked, [=,this]() mutable {
        subButtonsVisible_brandCars = !subButtonsVisible_brandCars;
        ui->pushButtonMazda->setVisible(subButtonsVisible_brandCars);
        ui->pushButtonHonda->setVisible(subButtonsVisible_brandCars);
        ui->pushButtonHyundai->setVisible(subButtonsVisible_brandCars);
        ui->pushButtonTesla->setVisible(subButtonsVisible_brandCars);

        if(subButtonsVisible_brandCars){ ui->pushButtonHelps->move(0,200);
                                            ui->pushButtonDocuments->move(0,230);
                                            ui->pushButtonVideo->move(0,250);
                                            ui->pushButtonDevices->move(0,270);

        }

        else {ui->pushButtonHelps->move(0,120);
                ui->pushButtonDocuments->move(0,150);
                ui->pushButtonVideo->move(0,170);
                ui->pushButtonDevices->move(0,190);

        }
         });


    connect(ui->pushButtonHelps, &QPushButton::clicked, [=,this]() mutable {
        subButtonsVisible_Help = !subButtonsVisible_Help;
        ui->pushButtonDevices->setVisible(subButtonsVisible_Help);
        ui->pushButtonDocuments->setVisible(subButtonsVisible_Help);
        ui->pushButtonVideo->setVisible(subButtonsVisible_Help);


    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startBackgroundProcess(const QString &command)
{
    QProcess *process = new QProcess(this);
    process->start("/bin/sh", QStringList() << "-c" << "sudo " + command + " &");

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start background process.";
    } else {
        qDebug() << "Background process started successfully.";
    }
}

void MainWindow::on_HomePushButton_clicked()
{

}

void MainWindow::on_pushButtonMazda_clicked()
{
    hide();
    md = new Mazda(this);
    md->show();
    startBackgroundProcess("ip link set dev can0 type can bitrate 500000 && sudo ip link set dev can0 up");
}



void MainWindow::on_pushButtonFord_clicked()
{

}


void MainWindow::on_pushButtonHonda_clicked()
{
    hide();
    hd =  new Honda1(this);
    hd->show();

    startBackgroundProcess("ip link set dev can0 type can bitrate 500000 && sudo ip link set dev can0 up");


}


void MainWindow::on_pushButtonHyundai_clicked()
{
    hide();
    Hynndai *hy ;
    hy = new Hynndai(this);
    hy->show();
    startBackgroundProcess("ip link set dev can0 type can bitrate 500000 && sudo ip link set dev can0 up");

}


void MainWindow::on_pushButtonTesla_clicked()
{
    hide();
    Tesla *tl ;
    tl=new Tesla(this);
    tl->show();
    startBackgroundProcess("ip link set dev can0 type can bitrate 500000 && sudo ip link set dev can0 up");

}


void MainWindow::on_pushButtonDocuments_clicked()
{
    QString Documents =  QFileDialog::getOpenFileName(this,"Open File","/home/DI/Documents/Document");
}


void MainWindow::on_pushButtonVideo_clicked()
{
    QString Video = QFileDialog::getOpenFileName(this,"Open File","/home/DI/Documents/Video");
}


void MainWindow::on_pushButtonDevices_clicked()
{
    QString Device = QFileDialog::getOpenFileName(this,"Open File","/home/DI/Documents/Video");
}

