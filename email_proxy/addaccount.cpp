#include "addaccount.h"
#include "ui_addaccount.h"
#include "QMessageBox"
#include "socket.h"
#include "controlfiles.h"
addAccount::addAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addAccount)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&addAccount::addUser);
}


void addAccount::addUser(){
    user=ui->user->text();
    password=ui->password->text();

    if(ui->user->text().isEmpty()){
           QMessageBox::information(this,"提醒","请输入账号");
      }
       else if(ui->password->text().isEmpty()){
           QMessageBox::information(this,"提醒","请输入密码");
      }
    else{
        socket *m_socket = new socket(user,password);
        qDebug() << "success";
        if(m_socket->checkAccount()){
            delete m_socket;
            controlFiles cF;
            cF.saveUser(user,password);
            this->hide();
        }
         else{
            QMessageBox::information(this,"提醒","账号密码错误");
        }
    }


}

addAccount::~addAccount()
{
    delete ui;
}
