#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_click_verification_code(bool);
    void onRequestFinished();
private:
    void test1();
    QNetworkReply *reply;
    QNetworkAccessManager networkAccessManager;
};

#endif // MAINWINDOW_H
