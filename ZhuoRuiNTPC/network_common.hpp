#ifndef NETWORK_COMMON_HPP
#define NETWORK_COMMON_HPP

#include<QString>
#include<QMap>
class NetworkCommon {
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
};

// 域名
const QString NetworkCommon::DOMAIN_URL = "http://192.168.1.241";
        // "https://ngpre.zr66.com";
// 发送短信
const char* const NetworkCommon::URL_SEND_SMS_CODE = "/as_notification/api/sms/v1/send_code";

#endif // NETWORK_COMMON_HPP
