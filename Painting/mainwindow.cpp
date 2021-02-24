#include "mainwindow.h"
#include <QPainter>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QColor g(0, 255, 0);
    painter.setPen(g);
    painter.drawEllipse(QRect(0, 0, 100, 100));
}
