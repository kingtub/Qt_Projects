#include "mainwindow.h"
#include"network_common.h"

#include"page_day_kline.h"
#include "page_fenshi.h"
#include "page_networktest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTabWidget *tabWidget = new QTabWidget;
    DayKPage *dayK = new DayKPage;
    FenShiPage *fenshi = new FenShiPage;
    NetworkTestPage *network_test = new NetworkTestPage;
    tabWidget->addTab(dayK, "日K");
    tabWidget->addTab(fenshi, "分时");
    tabWidget->addTab(network_test, "接口测试");
    setCentralWidget(tabWidget);
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    NetworkCommon::destroyInstance();
}
