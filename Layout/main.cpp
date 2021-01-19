#include "mainwidget.h"
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

// 这个程序显示如何使用布局
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;
    w.setWindowTitle("Enter your age");
    QSpinBox spinBox;
    QSlider slider(Qt::Horizontal);
    spinBox.setRange(0, 130);
    slider.setRange(0, 130);

    QObject::connect(&spinBox, SIGNAL(valueChanged(int)), &slider, SLOT(setValue(int)));
    QObject::connect(&slider, SIGNAL(valueChanged(int)), &spinBox, SLOT(setValue(int)));

    spinBox.setValue(35);

    QHBoxLayout qhBoxLayout;
    qhBoxLayout.addWidget(&spinBox);
    qhBoxLayout.addWidget(&slider);

    w.setLayout(&qhBoxLayout);


    w.show();

    return a.exec();
}
