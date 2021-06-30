#ifndef PLOT_KLINE_WITH_QCHART_HPP
#define PLOT_KLINE_WITH_QCHART_HPP

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCore/QDateTime>
#include "candlestickdatareader.h"

// 这是参考Qt SDK自带的example画的K线图
QChartView* plot_kline_with_sdk()
{
    QCandlestickSeries *hkKLineSeries = new QCandlestickSeries();
    hkKLineSeries->setName("K Line");
    hkKLineSeries->setIncreasingColor(QColor(Qt::red));
    hkKLineSeries->setDecreasingColor(QColor(Qt::green));

    // 港股数据
    QFile hkKLineData(":hk_stock_day_k");
    if (!hkKLineData.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QStringList categories;

    CandlestickDataReader dataReader(&hkKLineData);
    int i = 0;
    while (!dataReader.atEnd()) {
        QCandlestickSet *set = dataReader.readCandlestickSet();
        if (set) {
            hkKLineSeries->append(set);
            categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("yyyy-MM-dd");
            i++;
            if(i > 100) {
                break;
            }
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(hkKLineSeries);
    chart->setTitle("HK Stock Data");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

#endif // PLOT_KLINE_WITH_QCHART_HPP
