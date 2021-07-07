#include "page_networktest.h"
#include "network_common.h"
#include<QtWidgets>
TempStruct::TempStruct()
{

}
void TempStruct::clear()
{
    verificationCode = "";
    businessAccessToken = "";
}
TempStruct tempStruct;

CallbackCls::CallbackCls(NetworkTestPage *view)
{
    this->view = view;
}

void CallbackCls::operator ()(const QString &url, int errorCode,
                              QJsonDocument &document, const QString &errorStr) {
    qDebug()<<"url:"<<url<<", errorCode:"<<errorCode<<", errorStr:"
           <<errorStr;
    QJsonObject object = document.object();
    QString code = object.value("code").toString();
    QString msg = object.value("msg").toString();
    qDebug()<<"code:"<<code;
    qDebug()<<"msg:"<<msg;

    if(NetworkCommon::URL_SEND_SMS_CODE == url) {
        // 发送短信
        if(object.contains("data")) {
            // 说明是测试环境
            QString data = object.value("data").toString();
            //qDebug()<<"data:"<<data;
            view->msgEdit->append("sms_code:" + data + "\n");
            tempStruct.clear();
            tempStruct.verificationCode = data;
        }
    } else if(NetworkCommon::URL_USER_LOGIN_CODE == url) {
        // 用户验证码登陆
        QJsonObject data = object.value("data").toObject();
        QString userId = data.value("userId").toString();
        QString token = data.value("token").toString();
        QString businessAccessToken = data.value("businessAccessToken").toString();
        view->msgEdit->append("userId:" + userId + "\n");
        view->msgEdit->append("token:" + token + "\n");
        view->msgEdit->append("businessAccessToken:" + businessAccessToken + "\n");
        tempStruct.businessAccessToken = businessAccessToken;
    } else if(NetworkCommon::URL_SET_LOGIN_PWD == url) {
        QJsonObject data = object.value("data").toObject();
        QString phone = data.value("phone").toString();
        QString token = data.value("token").toString();
        view->msgEdit->append("phone:" + phone + "\n");
        view->msgEdit->append("token:" + token + "\n");
    } else if(NetworkCommon::URL_USER_LOGIN_PWD == url) {
        if(msg == "ok") {
            view->msgEdit->append("登录成功\n");
            QJsonObject data = object.value("data").toObject();
            QString userId = data.value("userId").toString();
            QString phone = data.value("phone").toString();
            QString token = data.value("token").toString();
            view->msgEdit->append("userId:" + userId + "\n");
            view->msgEdit->append("phone:" + phone + "\n");
            view->msgEdit->append("token:" + token + "\n");
        }
    }
}

NetworkTestPage::NetworkTestPage(QWidget *parent):QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *btn_get_verification_code = new QPushButton("注册第1步 - 获取验证码");
    QPushButton *btn_verification_code_login = new QPushButton("注册第2步 - 用户验证码登陆");
    QPushButton *btn_set_pwd = new QPushButton("注册第3步 - 设置登录密码");
    QPushButton *btn_login = new QPushButton("完成注册后，日常登录");
    msgEdit = new QTextEdit;

    layout->addWidget(btn_get_verification_code);
    layout->addWidget(btn_verification_code_login);
    layout->addWidget(btn_set_pwd);
    layout->addWidget(btn_login);
    layout->addWidget(msgEdit);

    connect(btn_get_verification_code, SIGNAL(clicked(bool)), this,
            SLOT(on_click_verification_code(bool)));
    connect(btn_verification_code_login, SIGNAL(clicked(bool)), this,
            SLOT(on_click_verification_code_login(bool)));
    connect(btn_set_pwd, SIGNAL(clicked(bool)), this,
            SLOT(on_click_set_pwd(bool)));
    connect(btn_login, SIGNAL(clicked(bool)), this,
            SLOT(on_click_login(bool)));
    setLayout(layout);

    callbackCls = std::make_shared<CallbackCls>(this);
}

NetworkTestPage::~NetworkTestPage()
{

}

// 测试一下和后台的接口通讯-发送短信验证码接口
void NetworkTestPage::on_click_verification_code(bool)
{
    QJsonObject obj;
    obj.insert("phone", "14704463375");
    obj.insert("countryCode", "86");
    obj.insert("smsCode", "1");
    NetworkCommon::getInstance()->postReq(NetworkCommon::URL_SEND_SMS_CODE, obj, *callbackCls);
}

void NetworkTestPage::on_click_verification_code_login(bool)
{              
    QJsonObject obj;
    obj.insert("phone", "14704463375");
    obj.insert("phoneArea", "86");
    obj.insert("verificationCode", tempStruct.verificationCode);
    NetworkCommon::getInstance()->postReq(NetworkCommon::URL_USER_LOGIN_CODE, obj, *callbackCls);
}

void NetworkTestPage::on_click_set_pwd(bool)
{
    QJsonObject obj;
    obj.insert("loginPassword", "123456");
    obj.insert("businessAccessToken", tempStruct.businessAccessToken);
    NetworkCommon::getInstance()->postReq(NetworkCommon::URL_SET_LOGIN_PWD, obj, *callbackCls);
}

void NetworkTestPage::on_click_login(bool)
{
    QJsonObject obj;
    obj.insert("phone", "14704463375");
    obj.insert("phoneArea", "86");
    obj.insert("loginPassword", "123456");
    NetworkCommon::getInstance()->postReq(NetworkCommon::URL_USER_LOGIN_PWD, obj, *callbackCls);
}
