#include "finddialog.h"


FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel("Find what:");
    lineEdit = new QLineEdit("");
    findButton = new QPushButton("Find");
    closeButton = new QPushButton("Close");
    caseCheckBox = new QCheckBox("Match case");
    backwardCheckBox = new QCheckBox("Search backward");
    caseCheckBox->setChecked(true);

    findButton->setDefault(true);
    findButton->setEnabled(false);

    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableFindButton(QString)));
    connect(findButton, SIGNAL(clicked(bool)), this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    h1 = new QHBoxLayout;
    h5 = new QHBoxLayout;
    v2 = new QVBoxLayout;
    v3 = new QVBoxLayout;
    h5->addWidget(label);
    h5->addWidget(lineEdit);
    v2->addWidget(findButton);
    v2->addWidget(closeButton);
    v3->addLayout(h5);
    v3->addWidget(caseCheckBox);
    v3->addWidget(backwardCheckBox);
    h1->addLayout(v3);
    h1->addLayout(v2);
    setLayout(h1);

    setWindowTitle("Find");
    setFixedHeight(sizeHint().height());
}

FindDialog::~FindDialog()
{
    // 非必要的， Qt在删除父对象时，自动删除子对象
    delete label;
    delete lineEdit;
    delete caseCheckBox;
    delete backwardCheckBox;
    delete findButton;
    delete closeButton;

    delete h1;
    delete v3;
    delete v2;
    delete h5;
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked()) {
        // emit Qt关键字， 代表发射信号SIGNAL
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.trimmed().isEmpty());
}
