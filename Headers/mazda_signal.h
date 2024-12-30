#ifndef MAZDA_SIGNAL_H
#define MAZDA_SIGNAL_H

#include <QDialog>

namespace Ui {
class mazda_signal;
}

class mazda_signal : public QDialog
{
    Q_OBJECT

public:
    explicit mazda_signal(QWidget *parent = nullptr);
    ~mazda_signal();

private slots:
    void on_buttonReturn_clicked();

private:
    Ui::mazda_signal *ui;
};

#endif // MAZDA_SIGNAL_H
