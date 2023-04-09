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
    _userName = username;
}

bool EmailReceive::isHaveEmail(QByteArray socketReceive)
{

    return false;
}

void EmailReceive::analyseEmail(QByteArray emailDetail){

}

int EmailReceive::getEmailNum(QByteArray socketReceive){
    QString r = socketReceive;
    QStringList strList = r.split(" ");
    QString i = strList[1];
    int num = i.toInt();
    return num;
}
