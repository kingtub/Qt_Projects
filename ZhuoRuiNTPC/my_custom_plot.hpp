#ifndef MY_CUSTOM_PLOT_HPP
#define MY_CUSTOM_PLOT_HPP

#include"qcustomplot.h"
class MyCustomPlot:public QCustomPlot {
public:
    MyCustomPlot(QWidget *parent=nullptr):QCustomPlot(parent) {

    }

    inline int getMoveOnDataIndex(QMouseEvent* event) {
        int i = -1;
        QVariant variant;
        layerableAt(event->pos(), false, &variant);
        if(!variant.isNull() && !variant.value<QCPDataSelection>().isEmpty()) {
            i = variant.value<QCPDataSelection>().dataRange().begin();
        }
        return i;
    }


    QCPLayerable * getMoveOnDataIndex(QMouseEvent* event, int *index) {
        *index = -1;
        QVariant variant;
        QCPLayerable *layerable = layerableAt(event->pos(), false, &variant);
        if(!variant.isNull() && !variant.value<QCPDataSelection>().isEmpty()) {
            *index = variant.value<QCPDataSelection>().dataRange().begin();
        }
        return layerable;
    }
};

struct MyQCPFinancialData {
    qreal timestamp;
    qreal open;
    qreal high;
    qreal low;
    qreal close;
};

class MyAxisTickerText : public QCPAxisTickerText
{
protected:
    virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE
    {
        Q_UNUSED(tickStep)
        QVector<double> result;
        if (mTicks.isEmpty())
            return result;

        auto start = mTicks.lowerBound(range.lower);
        auto end = mTicks.upperBound(range.upper);
        if (start != mTicks.constBegin()) --start;
        if (end != mTicks.constEnd()) ++end;

        int count = cleanMantissa(std::distance(start, end) / double(mTickCount + 1e-10));

        auto it = start;
        while (it != end) {
            result.append(it.key());
            int step = count;
            if (step == 0) ++it;
            while (--step >= 0 && it != end)
                ++it;
        }

        return result;
    }
};

#endif // MY_CUSTOM_PLOT_HPP
