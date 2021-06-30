#-------------------------------------------------
#
# Project created by QtCreator 2021-06-22T15:10:15
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ZhuoRuiNTPC
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        candlestickdatareader.cpp \
        qcustomplot.cpp \
    page_day_kline.cpp \
    page_fenshi.cpp

HEADERS += \
        mainwindow.h \
    network_common.hpp \
    candlestickdatareader.h \
    qcustomplot.h \
    plot_kline_with_qcp.hpp \
    plot_kline_with_sdk.hpp \
    plot_zhuoruidata_kline_with_qcp.hpp \
    my_custom_plot.hpp \
    page_day_kline.h \
    page_fenshi.h

RESOURCES += \
    zhuoruipc.qrc
