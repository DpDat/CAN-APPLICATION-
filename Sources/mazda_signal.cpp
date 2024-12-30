#include "mazda_signal.h"
#include "ui_mazda_signal.h"
#include "mazda.h"

Mazda *mazda_sig;
mazda_signal::mazda_signal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mazda_signal)
{
    ui->setupUi(this);
}

mazda_signal::~mazda_signal()
{
    delete ui;
}

void mazda_signal::on_buttonReturn_clicked()
{
    hide();
    mazda_sig = new Mazda(this);
    mazda_sig->show();
}

