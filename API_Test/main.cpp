#include "testmainwindow.h"
#include <QtWidgets>
#include <QApplication>
#include <QLabel>
#include "table.hpp"
#include "iconeditor.h"
#include "plotter.h"

void readFlightCurves(Plotter *plotter, const QString &fileName);

#define TAG 4

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if TAG == 0

    TestMainWindow w;
    //QLabel label("Test API");
    //w.setCentralWidget(&label);
    w.setCentralWidget(createTableWidget(9, 9));
    w.show();

#elif TAG == 1

    IconEditor iconEditor;
    iconEditor.setWindowTitle(QObject::tr("Icon Editor"));
    iconEditor.setIconImage(QImage(":/images/mouse.png"));
    iconEditor.show();

#elif TAG == 2

    Plotter plotter;
    plotter.setWindowTitle(QObject::tr("Jambi Plotter"));
    readFlightCurves(&plotter, ":/in1.txt");
    plotter.show();

#elif TAG == 3

    QTextEdit *editor1 = new QTextEdit;
    QTextEdit *editor2 = new QTextEdit;
    QTextEdit *editor3 = new QTextEdit;

    QSplitter splitter(Qt::Horizontal);
    splitter.addWidget(editor1);
    splitter.addWidget(editor2);
    splitter.addWidget(editor3);

    editor1->setPlainText("Mon enfant, ma soeur,\n"
                          "Songe  la douceur\n"
                          "D'aller l-bas vivre ensemble,\n"
                          "Aimer  loisir,\n"
                          "Aimer et mourir\n"
                          "Au pays qui te ressemble.");
    editor2->setPlainText("My child, my sister,\n"
                          "think of the sweetness\n"
                          "of going there to live together!\n"
                          "To love at leisure,\n"
                          "to love and to die\n"
                          "in a country that is the image of you!");
    editor3->setPlainText("Mein Kind, meine Schwester,\n"
                          "denke an den Traum\n"
                          "dort hin(unter) zu gehen um zusammen\n"
                          "zu leben und in aller Ruhe zu lieben,\n"
                          "Zu lieben und zu sterben\n"
                          "in dem Land, das dir gleicht.");

    splitter.setWindowTitle(QObject::tr("Splitter"));
    splitter.show();

#elif TAG == 4
    QScrollArea scrollArea;
    IconEditor iconEditor;
    iconEditor.setIconImage(QImage(":/images/mouse.png"));
    scrollArea.setWidget(&iconEditor);
    scrollArea.viewport()->setBackgroundRole(QPalette::Dark);
    scrollArea.viewport()->setAutoFillBackground(true);
    scrollArea.setWindowTitle("Icon Editor");
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    scrollArea.show();
#endif

    return a.exec();
}

void readFlightCurves(Plotter *plotter, const QString &fileName)
{
    QVector<QPointF> data[6];
    double factX = 0.0013;
    double factY[6] = { 0.0008, 0.1, 0.2, 0.2, 0.1, 0.8 };
    double offsY[6] = { +500, -55, +309, +308, 0, 0 };
    int pos[6] = { 3, 6, 7, 8, 9, 10 };
    QFile file(fileName);
    double offsX = 0.0;

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList coords = line.split(' ',
                                            QString::SkipEmptyParts);
            if (coords.count() >= 6) {
                double x = factX * coords[0].toDouble();
                if (data[0].isEmpty())
                    offsX = x;
                for (int i = 0; i < 6; ++i) {
                    double y = coords[pos[i]].toDouble();
                    data[i].append(QPointF(x - offsX,
                                           factY[i] * (y - offsY[i])));
                }
            }
        }
    }

    plotter->setCurveData(0, data[0]);
    plotter->setCurveData(1, data[1]);
    plotter->setCurveData(2, data[2]);
    plotter->setCurveData(3, data[3]);
    plotter->setCurveData(4, data[4]);
    plotter->setCurveData(5, data[5]);
}
