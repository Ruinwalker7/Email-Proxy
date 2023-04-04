#include "send_email.h"
#include "ui_send_email.h"
#include<QtNetwork>
#include "QByteArray"

send_email::send_email(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send_email)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&send_email::sendEmail);
}

void send_email::sendEmail(){



     port = 25;
     m_socket->connectToHost("smtp.163.com",25,QTcpSocket::ReadWrite);  //连接163邮箱
     m_socket->waitForConnected(1000);
    WaitAndReadData();
     m_socket->write("helo localhost\r\n");
    WaitAndReadData();
     m_socket->write("auth login\r\n");
    WaitAndReadData();
     m_socket->write(m_UserName.toBase64()+"\r\n");  //写入用户名
    WaitAndReadData();
     m_socket->write(m_Password.toBase64()+"\r\n");  //写入密码
     WaitAndReadData();
     m_socket->write("mail from: <"+m_UserName+">\r\n"); //发送的邮箱
     WaitAndReadData();
     m_socket->write("rcpt to: <"+sendIp+">\r\n"); //接收的邮箱
     WaitAndReadData();
     m_socket->write("data\r\n");  //开始写入
     WaitAndReadData();
     m_socket->write("from:<"+m_UserName+">\r\n");  //发送名称
     WaitAndReadData();
     m_socket->write("to:<"+sendIp+">");  //接受名称
     WaitAndReadData();
     m_socket->write("data\r\n");
     WaitAndReadData();
     m_socket->write("Subject:"+s_Title+"\r\n");  //标题
     m_socket->write("\r\n");
     m_socket->write(s_Content.append("\r\n")); //内容
     m_socket->write(".\r\n");
     WaitAndReadData();
     m_socket->write("quit\r\n");
     m_socket->disconnect();
}

void send_email::setUser(QString user,QString password){
       m_UserName = user.toUtf8();
       m_Password = password.toUtf8();

}

send_email::~send_email()
{
    delete ui;
}

QString send_email::WaitAndReadData()
{
    m_socket->waitForReadyRead(1000);
   QString m_ReceiverData =  m_socket->readAll();
   qDebug() << m_ReceiverData;
   return m_ReceiverData;
}
