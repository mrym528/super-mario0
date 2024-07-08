#include <QApplication>
#include <QDebug>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto mainwindow = new MainWindow();
    mainwindow->show();

    return QApplication::exec();
}

