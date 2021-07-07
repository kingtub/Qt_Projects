#ifndef PAGE_NETWORKTEST_H
#define PAGE_NETWORKTEST_H

#include <QWidget>
#include <QTextEdit>
#include <memory>

struct TempStruct {
    TempStruct();
    void clear();
    QString verificationCode;
    QString businessAccessToken;
};

class NetworkTestPage;
class CallbackCls {
public:
    CallbackCls(NetworkTestPage *);
    void operator()(const QString &, int, QJsonDocument &, const QString &);
private:
    NetworkTestPage *view;
};

class NetworkTestPage:public QWidget {
    Q_OBJECT
    friend class CallbackCls;
public:
    NetworkTestPage(QWidget *parent = 0);
    ~NetworkTestPage();
private slots:
    void on_click_verification_code(bool);
    void on_click_verification_code_login(bool);
    void on_click_set_pwd(bool);
    void on_click_login(bool);
private:
    std::shared_ptr<CallbackCls> callbackCls;
    QTextEdit *msgEdit;
};

#endif // PAGE_NETWORKTEST_H
