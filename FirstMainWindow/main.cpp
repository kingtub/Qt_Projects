#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow mainWin;
    //mainWin.show();

    // 为了能同时处理多个文档
    MainWindow *win = new MainWindow;
    win->show();

    return a.exec();
}
