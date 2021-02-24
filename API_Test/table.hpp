#ifndef TABLE_HPP
#define TABLE_HPP

#include <QTableWidget>
#include <string>

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

#endif // TABLE_HPP
