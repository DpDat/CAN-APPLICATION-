#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMaximizeButtonHint| Qt::WindowCloseButtonHint |Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    w.setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));

    w.show();

    return a.exec();
}
