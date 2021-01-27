#include "testmainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestMainWindow w;
    QLabel label("Test API");
    w.setCentralWidget(&label);
    w.show();

    return a.exec();
}
