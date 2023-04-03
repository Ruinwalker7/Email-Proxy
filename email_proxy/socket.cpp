#include "socket.h"
#include<QtNetwork>

socket::socket()
{
    m_socket = new QTcpSocket();
}

 socket::~socket(){
     m_socket->close();
 delete m_socket;
 }

socket::socket(QString user,QString password){
        m_socket = new QTcpSocket();
    m_UserName = user;
    m_Password = password;
    QStringList list = user.split("@");//QString字符串分割函数
    stmp_addr = "smtp."+list[1];
}

QString socket::WaitAndReadData()
{
   m_socket->waitForReadyRead(1000);
   QString m_ReceiverData =  m_socket->readAll();

   qDebug()<< m_socket->state();
   qDebug() << m_ReceiverData;
   return m_ReceiverData.mid(0,3);
}


bool socket::checkAccount(){
    int port = 25;
    qDebug() << stmp_addr;
    m_socket->connectToHost(stmp_addr,port,QTcpSocket::ReadWrite);  //连接163邮箱
    m_socket->waitForConnected(1000);
    m_socket->waitForReadyRead(1000);
    if(m_socket->state()==QAbstractSocket::UnconnectedState){
        return false;
    }

    m_socket->write("helo localhost\r\n");
    WaitAndReadData();
    if(m_socket->state()==QAbstractSocket::UnconnectedState){
        return false;
    }
    m_socket->write("auth login\r\n");
    WaitAndReadData();
    if(m_socket->state()==QAbstractSocket::UnconnectedState){
        return false;
    }
    m_socket->write(m_UserName.toUtf8().toBase64()+"\r\n");  //写入用户名
    WaitAndReadData();
    if(m_socket->state()==QAbstractSocket::UnconnectedState){
        return false;
    }

    m_socket->write(m_Password.toUtf8().toBase64()+"\r\n");  //写入密码
       if(WaitAndReadData()=="535"){
       return false;
       };
    m_socket->disconnectFromHost();
    m_socket->waitForDisconnected();
    return true;
}
