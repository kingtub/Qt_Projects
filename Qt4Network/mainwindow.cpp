#include "mainwindow.h"
#include"constants.hpp"

#include<QtWidgets>
#include<QtNetwork>

#include<QHostInfo>
#include<QString>
#include<QStringList>
#include<QJsonObject>
#include<QJsonDocument>
#include<QFile>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //QString hostInfo = getNetworkHostInfo();
    //label->setText(hostInfo);

    //getSupportSchemes();

    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *btn_get_verification_code = new QPushButton("验证码");
    QLineEdit *msgEdit = new QLineEdit;
    QPushButton *btn_login = new QPushButton("登录");
    QPushButton *btn_set_pwd = new QPushButton("设置密码");

    connect(btn_get_verification_code, SIGNAL(clicked(bool)), this,
            SLOT(on_click_verification_code(bool)));
    connect(btn_login, SIGNAL(clicked(bool)), this,
            SLOT(on_click_login(bool)));
    connect(btn_set_pwd, SIGNAL(clicked(bool)), this,
            SLOT(on_click_set_pwd(bool)));

    layout->addWidget(btn_get_verification_code);
    layout->addWidget(msgEdit);
    layout->addWidget(btn_login);
    layout->addWidget(btn_set_pwd);

    QWidget *whole = new QWidget;
    whole->setLayout(layout);
    setCentralWidget(whole);

    setWindowTitle(tr("Network Test"));
    setFixedHeight(sizeHint().height());
}

MainWindow::~MainWindow()
{

}

void MainWindow::onRequestFinished()
{
    QVariant data = reply->readAll();//读取全部数据
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(data.toByteArray(), &jsonError);
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        qDebug()<<"JSON解析正常";
        QJsonObject object = document.object();
        QString code = object.value("code").toString();
        QString msg = object.value("msg").toString();
        qDebug()<<"code:"<<code;
        qDebug()<<"msg:"<<msg;

        if(object.contains("data")) {
            QString data = object.value("data").toString();
            qDebug()<<"data:"<<data;
        }
    } else {
        if(document.isNull() == true) {
            qDebug()<<"document.isNull:" + reply->errorString();
        } else if(jsonError.error != QJsonParseError::NoError){
            qDebug()<<"jsonError.error:" + reply->errorString();
        }
    }

    reply->deleteLater();
    reply = Q_NULLPTR;
}

void MainWindow::on_click_verification_code(bool)
{
    QString domain_url = Constants::get_domain_url();
    QNetworkRequest request;

    // 发送https请求前准备工作;
    if(domain_url.startsWith("https")) {
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1SslV3);
        request.setSslConfiguration(conf);
    }

    request.setUrl(QUrl(domain_url + "/as_notification/api/sms/v1/send_code"));
    request.setRawHeader("Content-Type", "application/json;charset=utf-8");
    request.setRawHeader("osType", "web");
    request.setRawHeader("deviceId", "1234");

    QJsonObject obj;
    obj.insert("phone", "15889681345");
    obj.insert("countryCode", "86");
    obj.insert("smsCode", "4");
    QJsonDocument jdoc(obj);
    QString str = QString(jdoc.toJson());//QJsonDocument转QString
    QByteArray content = str.toUtf8();


    reply = networkAccessManager.post(request, content);

    /*connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(slotSslErrors(QList<QSslError>)));*/
    connect(reply, SIGNAL(finished()), this, SLOT(onRequestFinished()));
}

void MainWindow::on_click_login(bool)
{

}

void MainWindow::on_click_set_pwd(bool)
{

}

QString MainWindow::getNetworkHostInfo()
{
    QString hostInfo = "";
    hostInfo += "localhostname: ";
    hostInfo += QHostInfo::localHostName();
    hostInfo += " \n";
    hostInfo += "ip: ";
    foreach (const auto & addr, QHostInfo::fromName(QHostInfo::localHostName())
             .addresses()) {
        hostInfo += addr.toString() + "\n";
    }
    return hostInfo;
}

QStringList MainWindow::getSupportSchemes()
{
    QNetworkAccessManager manager(this);
    //qDebug() << manager.supportedSchemes();
}
