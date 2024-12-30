#ifndef MAZDA_H
#define MAZDA_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Mazda;
}

class Mazda : public QDialog
{
    Q_OBJECT

public:
    explicit Mazda(QWidget *parent = nullptr);
    ~Mazda();

private slots:

    void on_buttonHome_clicked();

    void on_pushButtonMonitor_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Mazda *ui;

    void startBackgroundProcess(const QString &command) ;

};

#endif // MAZDA_H
