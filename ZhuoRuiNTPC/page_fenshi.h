#ifndef FENSHIPAGE_H
#define FENSHIPAGE_H

#include <QWidget>
#include"my_custom_plot.hpp"

struct DataItem {
      qreal  time;
      qreal  open;
      qreal  high;
      qreal  low;
      qreal  close;
      qreal  sharestraded;
      qreal  turnover;
      qreal  vwap;
};

struct MyData {
     int type;
     QString ts;
     QString code;
     qreal preClose;
     QList<DataItem> items;
     void addItem(const DataItem &i) {
         items.append(i);
     }
};

// 显示分时线的页面
class FenShiPage:public QWidget {
    Q_OBJECT
public:
    FenShiPage(QWidget *parent = 0);
    ~FenShiPage();
    void showLines();

private slots:
    void my_mouseMove(QMouseEvent* event);
private:
    MyCustomPlot* customPlot;
    MyData theData;
};

#endif // FENSHIPAGE_H
