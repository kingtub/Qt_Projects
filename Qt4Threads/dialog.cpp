#include "dialog.h"
#include<QHBoxLayout>
#include<QCloseEvent>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    threadABtn.setText(tr("start thread A"));
    threadBBtn.setText(tr("start thread B"));
    quitBtn.setText(tr("quit"));
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(&threadABtn);
    hlayout->addWidget(&threadBBtn);
    hlayout->addWidget(&quitBtn);

    thA.setMsg("A");
    thB.setMsg("B");

    connect(&threadABtn, SIGNAL(clicked()), this, SLOT(onClickABtn()));
    connect(&threadBBtn, SIGNAL(clicked()), this, SLOT(onClickBBtn()));
    connect(&quitBtn, SIGNAL(clicked()), this, SLOT(onClickquitBtn()));

    setLayout(hlayout);
    setWindowTitle(tr("Threads"));
}

Dialog::~Dialog()
{

}

void Dialog::onClickABtn() {
    if(thA.isRunning()) {
        thA.stop();
        threadABtn.setText(tr("start thread A"));
    } else {
        thA.start();
        threadABtn.setText(tr("stop thread A"));
    }
}

void Dialog::onClickBBtn() {
    if(thB.isRunning()) {
        thB.stop();
        threadBBtn.setText(tr("start thread B"));
    } else {
        thB.start();
        threadBBtn.setText(tr("stop thread B"));
    }
}

void Dialog::onClickquitBtn() {
    close();
}

void Dialog::closeEvent(QCloseEvent *event) {
    clearRes();
    event->accept();
}

void Dialog::clearRes() {
    thA.stop();
    thB.stop();
    thA.wait();
    thB.wait();
}
