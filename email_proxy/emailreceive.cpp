#include "emailreceive.h"
#include "ui_emailreceive.h"
#include "QDebug"
#include "controlfiles.h"

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
    QString r = socketReceive;
    QStringList strList = r.split(" ");
    QString i = strList[2];
    i.chop(2);
    qDebug() <<i<<"\n";
    controlFiles *cf = new controlFiles();
    cf->isHaveEmail(_userName,i );
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
