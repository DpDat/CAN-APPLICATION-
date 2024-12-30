#ifndef TESLA_H
#define TESLA_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Tesla;
}

class Tesla : public QDialog
{
    Q_OBJECT

public:
    explicit Tesla(QWidget *parent = nullptr);
    ~Tesla();

private slots:
    void on_buttonHome_clicked();

    void on_pushButtonMonitor_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Tesla *ui;
    void startBackgroundProcess(const QString &command) ;
};

#endif // TESLA_H
