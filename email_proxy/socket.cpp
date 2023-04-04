#include "socket.h"
#include<QtNetwork>


 socket::~socket(){
     m_socket->disconnect();
     m_socket->close();
     delete m_socket;
 }

socket::socket(QByteArray _user,QByteArray _password){
    m_socket = new QTcpSocket();
    userName = _user;
    password = _password;
    QString user = userName;
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

bool socket::sendEmail(QByteArray s_title, QByteArray s_Content, QByteArray sendIp){
    m_socket->write("mail from: <"+userName+">\r\n"); //发送的邮箱
    WaitAndReadData();
    m_socket->write("rcpt to: <"+sendIp+">\r\n"); //接收的邮箱
    WaitAndReadData();
    m_socket->write("data\r\n");  //开始写入
    WaitAndReadData();
    m_socket->write("from:<"+userName+">\r\n");  //发送名称
    WaitAndReadData();
    m_socket->write("to:<"+sendIp+">");  //接受名称
    WaitAndReadData();
    m_socket->write("data\r\n");
    WaitAndReadData();
    m_socket->write("Subject:"+s_title+"\r\n");  //标题
    m_socket->write("\r\n");
    m_socket->write(s_Content+"\r\n"); //内容
    m_socket->write(".\r\n");
    WaitAndReadData();
    m_socket->write("quit\r\n");
    return true;
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
    m_socket->write(userName.toBase64()+"\r\n");  //写入用户名
    WaitAndReadData();
    if(m_socket->state()==QAbstractSocket::UnconnectedState){
        return false;
    }

    m_socket->write(password.toBase64()+"\r\n");  //写入密码
       if(WaitAndReadData()=="535"){
       return false;
       };
    return true;
}
