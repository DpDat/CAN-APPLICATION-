#ifndef HYNNDAI_H
#define HYNNDAI_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Hynndai;
}

class Hynndai : public QDialog
{
    Q_OBJECT

public:
    explicit Hynndai(QWidget *parent = nullptr);
    ~Hynndai();

private slots:
    void on_buttonHome_clicked();

    void on_pushButtonMonitor_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    void startBackgroundProcess(const QString &command) ;
    Ui::Hynndai *ui;
};

#endif // HYNNDAI_H
