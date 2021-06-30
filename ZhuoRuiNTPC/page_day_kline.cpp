//#include <QtCharts/QChartView>
//#include "plot_kline_with_sdk.hpp"
//#include "plot_kline_with_qcp.hpp"
//#include "plot_zhuoruidata_kline_with_qcp.hpp"

#include"page_day_kline.h"

DayKPage::DayKPage(QWidget *parent):QWidget(parent)
{
    showKLine();
    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(customPlot);
    setLayout(boxLayout);
}

DayKPage::~DayKPage()
{

}

void DayKPage::my_mouseMove(QMouseEvent* event)
{
    if(customPlot == 0) {
        return;
    }
    int index = customPlot->getMoveOnDataIndex(event);
    if(index != -1) {
        QSharedPointer<MyQCPFinancialData> di = dayKDataList.at(index);
        qreal timestamp = di->timestamp;

        QString msg = QStringLiteral("Open:%1, High:%2, Low:%3, Close:%4\nDay:%5").
                arg(di->open).arg(di->high).arg(di->low).arg(di->close)
                .arg(QDateTime::fromMSecsSinceEpoch(timestamp).toString("yyyy-MM-dd"));
        QToolTip::showText(QCursor::pos(), msg);
    }
}

void DayKPage::showKLine()
{
    // 1、这是参考Qt SDK自带的example画的K线图
    /*QChartView *chartView = plot_kline_with_sdk();
    if(!chartView) {
        return;
    }
    this->setCentralWidget(chartView);
    this->resize(800, 600);*/

    // 2、这是利用Qt第三方库QCustomPlot来画的k线，功能丰富
    /*QCustomPlot* qcp = new QCustomPlot;
    setupShangHaiIndexDemo(qcp);
    this->setCentralWidget(qcp);
    this->resize(800, 600);*/

    // 3、 这是利用Qt第三方库QCustomPlot来画的k线，使用卓锐的真实数据
    if(customPlot != nullptr) {
        return;
    }
    customPlot = new MyCustomPlot;

    const QColor BrushPositive("#ec0000");
    const QColor PenPositive("#8a0000");
    const QColor BrushNegative("#00da3c");
    const QColor PenNegative("#008f28");

    QSharedPointer<QCPAxisTickerText> textTicker(new MyAxisTickerText);  // 文字轴
    textTicker->setTickCount(8);


    // 这是真实的港股数据，某一只股票的日K数据
    QFile hkKLineData(":hk_stock_day_k");
    if (!hkKLineData.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //int tem = 0;
    QTextStream inStream(&hkKLineData);
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        if (line.startsWith("link") || line.isEmpty())
            continue;

        QStringList strList = line.split(",", QString::SkipEmptyParts);

        if (strList.count() < 5) {
            continue;
        }

        const qreal timestamp = strList.at(0).toDouble();
        const qreal open = strList.at(1).toDouble();
        const qreal high = strList.at(2).toDouble();
        const qreal low = strList.at(3).toDouble();
        const qreal close = strList.at(4).toDouble();

        QSharedPointer<MyQCPFinancialData> df(new MyQCPFinancialData);
        df->timestamp = timestamp;
        df->open = open;
        df->high = high;
        df->low = low;
        df->close = close;

        // 数据要按照时间顺序来
        dayKDataList.insert(0, df);

//        tem++;
//        if(tem > 5) {
//            break;
//        }
    }

    int i = 0;
    const int count = dayKDataList.count();
    while(i < count) {
        QSharedPointer<MyQCPFinancialData> si = dayKDataList.at(i);

        QCPFinancialData data;
        data.key = i;
        data.open = si->open;
        data.high = si->high;
        data.low = si->low;
        data.close = si->close;

        datas.add(std::move(data));

        textTicker->addTick(i, QDateTime::fromMSecsSinceEpoch(si->timestamp).
                            toString("yyyy-MM-dd"));
        i++;

    }

    QCPFinancial *financial = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    financial->setName("日K");

    financial->setBrushPositive(BrushPositive);
    financial->setBrushNegative(BrushNegative);
    //financial->setBrushPositive(Qt::NoBrush);
    //financial->setBrushNegative(Qt::NoBrush);
    financial->setPenPositive(PenPositive);
    financial->setPenNegative(PenNegative);
    financial->data()->set(datas);

    customPlot->xAxis->setTicker(textTicker);
    customPlot->rescaleAxes();
    customPlot->xAxis->scaleRange(1.05, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.05, customPlot->yAxis->range().center());
    //customPlot->legend->setVisible(true);  // 显示插图
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)),
            this, SLOT(my_mouseMove(QMouseEvent*)));
}
