#include"page_fenshi.h"

FenShiPage::FenShiPage(QWidget *parent):QWidget(parent)
{
    showLines();
    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(customPlot);
    setLayout(boxLayout);
}

FenShiPage::~FenShiPage()
{

}

void FenShiPage::my_mouseMove(QMouseEvent* event)
{
    if(customPlot == 0) {
        return;
    }
    int index = 0;
    QCPLayerable * layerable = customPlot->getMoveOnDataIndex(event, &index);
    if(index != -1 && layerable != nullptr) {
        DataItem di = theData.items.at(index);
        qreal time = di.time;
        qreal value = 0;
        if(layerable == customPlot->graph(0)) {
            value = di.close;
        } else if(layerable == customPlot->graph(1)) {
            value = di.vwap;
        }
        QString msg = QStringLiteral("%1\nTime:%2").arg(value)
                .arg(QDateTime::fromMSecsSinceEpoch(time).toString("hh:mm"));
//        QString msg = QStringLiteral("%1\nTime:%2 \n%3").arg(value)
//                .arg(QDateTime::fromMSecsSinceEpoch(time).toString("hh:mm"))
//                .arg(index);
        QToolTip::showText(QCursor::pos(), msg);
    }
}

void FenShiPage::showLines()
{
    customPlot = new MyCustomPlot;

    const QColor brushColor("#375471");
    const QColor blueLineColor("#277591");
    const QColor yellowLineColor("#E2BD1F");
    const QColor gray(Qt::gray);

    QSharedPointer<QCPAxisTickerText> textTicker(new MyAxisTickerText);  // 文字轴
    textTicker->setTickCount(8);


    // 这是真实的港股数据，某一只股票的某日分时数据
    QFile hkFenshiData(":hk_stock_day_fenshi");
    if (!hkFenshiData.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray ba;

    QTextStream inStream(&hkFenshiData);
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        ba.append(line);
    }

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(ba, &jsonError);
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        qDebug()<<"JSON解析正常";
        QJsonObject object = document.object();
        
        QJsonObject da = object.value("data").toObject();
        theData.type = da.value("type").toInt();
        theData.ts = da.value("ts").toString();
        theData.code = da.value("code").toString();
        theData.preClose = da.value("preClose").toDouble();
        QJsonArray list = da.value("list").toArray();

        qDebug()<<"stock:"<<theData.ts;
        qDebug()<<"stockcode:"<<theData.code;

        int itemCount = list.count();
        QVector<double> x(itemCount), yBlue(itemCount), yYellow(itemCount),
                yPreClose(itemCount, theData.preClose);

        for(int i = 0; i < itemCount; i++) {
            QJsonObject o = list.at(i).toObject();
            DataItem item;
            item.time = o.value("time").toDouble();
            item.open = o.value("open").toDouble();
            item.high = o.value("high").toDouble();
            item.low = o.value("low").toDouble();
            item.close = o.value("close").toDouble();
            item.sharestraded = o.value("sharestraded").toDouble();
            item.turnover = o.value("turnover").toDouble();
            item.vwap = o.value("vwap").toDouble();
            theData.addItem(item);

            textTicker->addTick(i, QDateTime::fromMSecsSinceEpoch(item.time).
                                toString("hh:mm"));

            x[i] = i;
            yBlue[i] = item.close;
            yYellow[i] = item.vwap;
        }

        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(blueLineColor));
        //customPlot->graph(0)->setBrush(QBrush(brushColor));
        customPlot->graph(0)->setBrush(Qt::NoBrush);
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(yellowLineColor));
        //customPlot->addGraph();
        //customPlot->graph(2)->setPen(QPen(gray));

        customPlot->xAxis2->setVisible(true);
        customPlot->xAxis2->setTickLabels(false);
        customPlot->yAxis2->setVisible(true);
        customPlot->yAxis2->setTickLabels(false);
        // make left and bottom axes always transfer their ranges to right and top axes:
        connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
        // pass data points to graphs:
        customPlot->graph(0)->setData(x, yBlue);
        customPlot->graph(1)->setData(x, yYellow);
        //customPlot->graph(2)->setData(x, yPreClose);

        // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
        customPlot->graph(0)->rescaleAxes();
        // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
        customPlot->graph(1)->rescaleAxes(true);

        //customPlot->graph(2)->rescaleAxes(true);
        //customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDot);


        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        customPlot->xAxis->setTicker(textTicker);

        connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)),
                this, SLOT(my_mouseMove(QMouseEvent*)));
    } else {
        qDebug()<<"JSON decode error";
    }

}
