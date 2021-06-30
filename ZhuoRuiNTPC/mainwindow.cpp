#include "mainwindow.h"
#include"network_common.hpp"

#include<QtWidgets>
#include<QtNetwork>
#include"page_day_kline.h"
#include "page_fenshi.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTabWidget *tabWidget = new QTabWidget;
    DayKPage *dayK = new DayKPage;
    FenShiPage *fenshi = new FenShiPage;
    tabWidget->addTab(dayK, "日K");
    tabWidget->addTab(fenshi, "分时");
    setCentralWidget(tabWidget);
    resize(800, 600);
}

MainWindow::~MainWindow()
{

}

void MainWindow::test1()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *btn_get_verification_code = new QPushButton("验证码");
    QLineEdit *msgEdit = new QLineEdit;

    connect(btn_get_verification_code, SIGNAL(clicked(bool)), this,
            SLOT(on_click_verification_code(bool)));
    layout->addWidget(btn_get_verification_code);
    layout->addWidget(msgEdit);

    QWidget *whole = new QWidget;
    whole->setLayout(layout);
    setCentralWidget(whole);

    setWindowTitle(tr("Network Test"));
    setFixedHeight(sizeHint().height());
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

// 测试一下和后台的接口通讯-发送短信验证码接口
void MainWindow::on_click_verification_code(bool)
{
    QString domain_url = NetworkCommon::DOMAIN_URL;
    QNetworkRequest request;

    // 发送https请求前准备工作。若是https，需要做一些配置。
    if(domain_url.startsWith("https")) {
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1SslV3);
        request.setSslConfiguration(conf);
    }

    request.setUrl(QUrl(domain_url + NetworkCommon::URL_SEND_SMS_CODE));
    QMap<QString, QString> headersMap = NetworkCommon::generate_common_headers();
    QMapIterator<QString, QString> i(headersMap);
    while(i.hasNext()) {
        i.next();
        request.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
    }

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
