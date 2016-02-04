/*
 * Video Player Demo
 *
 * Version 0.1
 *
 * 2016-02-03
 *
 * Copyright by Zongzhi Tang
 */


#include "mainwindow.h"
#include <QApplication>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
