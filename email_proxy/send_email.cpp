#include "send_email.h"
#include "ui_send_email.h"
#include<QtNetwork>
#include "QByteArray"

send_email::send_email(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send_email)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&send_email::sendEmail);
}

void send_email::sendEmail(){
    s_Title = ui->title->text().toUtf8();
    s_Content = ui->textEdit->toPlainText().toUtf8();
    sendIp = ui->toIP->text().toUtf8();
    m_socket = new socket(m_UserName,m_Password);
    m_socket ->checkAccount();
    m_socket ->sendEmail(s_Title,s_Content,sendIp);
    delete m_socket;
}

void send_email::setUser(QString user,QString password){
    m_UserName = user.toUtf8();
    m_Password = password.toUtf8();
}

send_email::~send_email()
{
    delete ui;
}

