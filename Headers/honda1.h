#ifndef HONDA1_H
#define HONDA1_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Honda1;
}

class Honda1 : public QDialog
{
    Q_OBJECT

public:
    explicit Honda1(QWidget *parent = nullptr);
    ~Honda1();


private slots:

    void on_buttonHome_clicked();


    void on_pushButtonMonitor_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Honda1 *ui;

     void startBackgroundProcess(const QString &command) ;
};

#endif // HONDA1_H
