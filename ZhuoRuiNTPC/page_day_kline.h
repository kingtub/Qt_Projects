#ifndef PAGE_DAY_KLINE_H
#define PAGE_DAY_KLINE_H

#include <QWidget>
#include"my_custom_plot.hpp"


// 显示日K线的页面
class DayKPage:public QWidget {
    Q_OBJECT
public:
    DayKPage(QWidget *parent = 0);
    ~DayKPage();
    void showKLine();

private slots:
    void my_mouseMove(QMouseEvent* event);
private:
    MyCustomPlot* customPlot;
    QCPDataContainer<QCPFinancialData> datas;
    QList<QSharedPointer<MyQCPFinancialData>> dayKDataList;
};



#endif // PAGE_DAY_KLINE_H
