#ifndef THREAD_H
#define THREAD_H

#include<QThread>
#include<QString>

class MyThread:public QThread
{
    Q_OBJECT
public:
    MyThread();
    void stop();
    void setMsg(const QString &msg);

protected:
     void run() override;

private:
    volatile bool stopFlag;
    QString msg;
};

#endif // THREAD_H
