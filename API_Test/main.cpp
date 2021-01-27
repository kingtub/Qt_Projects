#include "testmainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QTableWidget>
#include <string>

QTableWidget * createTableWidget(int row, int column);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestMainWindow w;
    //QLabel label("Test API");
    //w.setCentralWidget(&label);


    w.setCentralWidget(createTableWidget(9, 9));
    w.show();

    return a.exec();
}

// 电子表格控件
QTableWidget *createTableWidget(int row, int column)
{
    QTableWidget *tw  = new QTableWidget;
    tw->setRowCount(0);
    tw->setColumnCount(0);
    tw->setRowCount(row);
    tw->setColumnCount(column);

    std::string c = "C";
    for(int i = 0; i < column; i++) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString((c + std::to_string(i + 1)).c_str()));
        tw->setHorizontalHeaderItem(i, item);
    }
    return tw;
}
