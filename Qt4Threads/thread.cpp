#include "thread.h"
#include<iostream>

MyThread::MyThread()
{
    stopFlag = false;
}

void MyThread::run() {
    while(!stopFlag) {
        std::cerr<<qPrintable(msg);
    }
    stopFlag = false;
    std::cerr<<std::endl;
}

void MyThread::setMsg(const QString &msg) {
    this->msg = msg;
}

void MyThread::stop() {
    stopFlag = true;
}
