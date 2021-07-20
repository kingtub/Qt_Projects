#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include<QNetworkAccessManager>
#include<QNetworkReply>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QString getNetworkHostInfo();
    QStringList getSupportSchemes();
private slots:
    void on_click_verification_code(bool);
    void on_click_login(bool);
    void on_click_set_pwd(bool);
    void onRequestFinished();
private:
    QNetworkAccessManager networkAccessManager;
    QNetworkReply *reply;
};

#endif // MAINWINDOW_H
