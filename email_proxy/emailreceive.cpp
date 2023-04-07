#include "emailreceive.h"
#include "ui_emailreceive.h"

EmailReceive::EmailReceive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmailReceive)
{
    ui->setupUi(this);
}

EmailReceive::~EmailReceive()
{
    delete ui;
}


void EmailReceive::setUserName(QString username){
    _username = username;
}

int EmailReceive::getEmailNum(QByteArray socketReceive){
    QString r = socketReceive;
    QStringList strList = r.split(" ");
    QString i = strList[1];
    int num = i.toInt();
    return num;
}
