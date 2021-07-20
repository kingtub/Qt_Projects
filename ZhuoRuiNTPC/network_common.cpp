#include "network_common.h"

NetworkCommon::NetworkCommon() {

}
NetworkCommon::~NetworkCommon() {
    reqs.clear();
}

NetworkCommon* NetworkCommon::instance = Q_NULLPTR;
mutex NetworkCommon::mut;
NetworkCommon* NetworkCommon::getInstance()
{
    if(instance == Q_NULLPTR) {
        lock_guard<mutex> lm(mut);
        if(instance == Q_NULLPTR) {
            instance = new NetworkCommon;
        }
    }

    return instance;
}

void NetworkCommon::destroyInstance()
{
    if(instance != Q_NULLPTR) {
        delete instance;
        instance = Q_NULLPTR;
    }
}

void NetworkCommon::postReq(const QString &url, const QJsonObject &params, const function<void(const QString &, int, QJsonDocument &, const QString &)> &callback)
{
    QString domain_url = DOMAIN_URL;
    QNetworkRequest request;

    // 发送https请求前准备工作。若是https，需要做一些配置。
    if(domain_url.startsWith("https")) {
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1SslV3);
        request.setSslConfiguration(conf);
    }

    QString url_final = domain_url + url;
    request.setUrl(QUrl(url_final));
    QMap<QString, QString> headersMap = generate_common_headers();
    QMapIterator<QString, QString> i(headersMap);
    while(i.hasNext()) {
        i.next();
        request.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
    }

    QJsonDocument jdoc(params);
    QString str = QString(jdoc.toJson());//QJsonDocument转QString
    QByteArray content = str.toUtf8();

    networkAccessManager.post(request, content);
    connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)),
              this, SLOT(onRequestFinished(QNetworkReply*)));
    /*
    reply = networkAccessManager.post(request, content);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(slotSslErrors(QList<QSslError>)));
    connect(reply, SIGNAL(finished()), this, SLOT(onRequestFinished()));
    */

    reqs.insert(url_final, callback);
}

void NetworkCommon::onRequestFinished(QNetworkReply* reply)
{
    QVariant data = reply->readAll();//读取全部数据
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(data.toByteArray(), &jsonError);
    QString key = reply->url().toString();
    if(reqs.contains(key)) {
        bool good = !document.isNull() && (jsonError.error == QJsonParseError::NoError);
        QString errStr = good?"":reply->errorString();
        auto func = reqs.value(key);
        func(key.mid(DOMAIN_URL.length()), good?0:1, document, errStr);
        reqs.remove(key);
    } else {
        //qDebug()<<"Not contains key";
    }
    reply->deleteLater();
    reply = Q_NULLPTR;

    /*if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
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
    }*/
}

// 域名
const QString NetworkCommon::DOMAIN_URL = "http://192.168.1.241";
        // "https://ngpre.zr66.com";
// 发送短信
const char* const NetworkCommon::URL_SEND_SMS_CODE = "/as_notification/api/sms/v1/send_code";
const char* const NetworkCommon::URL_USER_LOGIN_CODE = "/as_user/api/user_account/v1/user_login_code";
const char* const NetworkCommon::URL_SET_LOGIN_PWD = "/as_user/api/user_account/v1/set_login_password";
const char* const NetworkCommon::URL_USER_LOGIN_PWD = "/as_user/api/user_account/v1/user_login_pwd";
