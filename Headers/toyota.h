#ifndef TOYOTA_H
#define TOYOTA_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Toyota;
}

class Toyota : public QDialog
{
    Q_OBJECT

public:
    explicit Toyota(QWidget *parent = nullptr);
    ~Toyota();

private slots:
    void on_buttonHome_clicked();

    void on_pushButtonMonitor_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Toyota *ui;

    void startBackgroundProcess(const QString &command) ;
};

#endif // TOYOTA_H
