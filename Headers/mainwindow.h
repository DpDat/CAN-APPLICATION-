#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mazda.h"
#include "honda1.h"
#include <QProcess>
#include "hynndai.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_HomePushButton_clicked();

    void on_pushButtonMazda_clicked();

    void on_pushButtonFord_clicked();

    void on_pushButtonHonda_clicked();

    void on_pushButtonHyundai_clicked();

    void on_pushButtonTesla_clicked();

    void on_pushButtonDocuments_clicked();

    void on_pushButtonVideo_clicked();

    void on_pushButtonDevices_clicked();

private:
    Ui::MainWindow *ui;

    void startBackgroundProcess(const QString &command);
};
#endif // MAINWINDOW_H
