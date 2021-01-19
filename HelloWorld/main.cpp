#include "mainwindow.h"
#include <QApplication>
#include<QLabel>
#include<QPushButton>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // test 1
//    MainWindow w;
//    w.show();


    // test2
//    QLabel label("You are good");
//    label.show();


    // test3
    QPushButton btn("Click me to quit");
    QObject::connect(&btn, SIGNAL(clicked()), &a, SLOT(quit()));
    btn.show();


    return a.exec();
}

