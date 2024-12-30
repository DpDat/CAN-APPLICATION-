#ifndef HONDA_H
#define HONDA_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Honda;
}

class Honda : public QDialog
{
    Q_OBJECT

public:
    explicit Honda(QWidget *parent = nullptr);
    ~Honda();

private slots:

    void on_buttonHome_clicked();

    void on_pushButtonMonitor_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Honda *ui;

    void startBackgroundProcess(const QString &command);
};

#endif
