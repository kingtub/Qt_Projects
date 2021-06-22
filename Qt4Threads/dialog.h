#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"thread.h"
#include<QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void onClickABtn();
    void onClickBBtn();
    void onClickquitBtn();

private:
    void clearRes();
    QPushButton threadABtn;
    QPushButton threadBBtn;
    QPushButton quitBtn;
    MyThread thA, thB;
};

#endif // DIALOG_H
