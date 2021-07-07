#ifndef NETWORK_COMMON_HPP
#define NETWORK_COMMON_HPP

#include<mutex>
#include<functional>

#include <QString>
#include <QMap>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include<QJsonDocument>
#include<QJsonObject>

using namespace std;
class NetworkCommon:public QObject {
    Q_OBJECT
public:
    /**
     * @brief generate_common_headers 获取共同的请求头信息
     * @return 共同的请求头信息
     */
    static inline QMap<QString, QString> generate_common_headers() {
        QMap<QString, QString> map;
        map.insert("Content-Type", "application/json;charset=utf-8");
        map.insert("osType", "web");
        map.insert("deviceId", "1234");
        return map;
    }

    // 域名
    //内网测试 http://192.168.1.241
    //内网开发 http://192.168.1.181
    //外网预发布 https://ngpre.zr66.com
    static const QString DOMAIN_URL;
    //static const QString str2;
    // 发送短信
    static const char* const URL_SEND_SMS_CODE;
    // 用户验证码登陆
    static const char* const URL_USER_LOGIN_CODE;
    // 设置登录密码
    static const char* const URL_SET_LOGIN_PWD;
    // 用户密码登陆
    static const char* const URL_USER_LOGIN_PWD;

    static NetworkCommon *getInstance();
    static void destroyInstance();

private:
    static NetworkCommon *instance;
    static mutex mut;
private:
    NetworkCommon();
    QNetworkAccessManager networkAccessManager;
    QMap<QString, function<void(const QString &, int, QJsonDocument &, const QString &)>> reqs;
private slots:
    void onRequestFinished(QNetworkReply*);
public:
    ~NetworkCommon();
    void postReq(const QString &url, const QJsonObject &params, const function<void(const QString &, int, QJsonDocument &, const QString &)> &callback);
};

#endif // NETWORK_COMMON_HPP
