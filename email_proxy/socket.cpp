#include "socket.h"

socket::~socket(){
     m_socket->disconnect();
     m_socket->close();
     delete m_socket;
 }

socket::socket(QByteArray _user, QByteArray _password){
    m_socket = new QTcpSocket();
    userName = _user;
    password = _password;
    QString user = userName;
    QStringList list = user.split("@");//QString字符串分割函数
    stmp_addr = "smtp."+list[1];
    pop3_addr = "pop." + list[1];
}

QString socket::WaitAndReadData()
{
   m_socket->waitForReadyRead(1000);
   QByteArray ReceiverData =  m_socket->readAll();
   qDebug()<< m_socket->state();
   qDebug() << ReceiverData;
   return ReceiverData.mid(0,3);
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
    m_socket->write("to:<"+sendIp+">\r\n");  //接受名称
    WaitAndReadData();
    m_socket->write("subject:"+s_title+"\r\n");  //标题
    m_socket->write("\r\n");
    m_socket->write(s_Content+"\r\n"); //内容
    m_socket->write(".\r\n");
    WaitAndReadData();
    m_socket->write("quit\r\n");
    WaitAndReadData();
    return true;
}

bool socket::Pop3_receiver(EmailReceive *receiver){
    int port = 110;
    qDebug()<<pop3_addr;
    m_socket->connectToHost(pop3_addr,port,QTcpSocket::ReadWrite);  //连接163邮箱
    m_socket->waitForConnected(1000);
    m_socket->waitForReadyRead(1000);
    m_socket->write("user "+userName+"\r\n");  //写入用户名
    WaitAndReadData();
    m_socket->write("pass "+password+"\r\n");  //写入用户名
    WaitAndReadData();
    m_socket->write("stat\r\n");
    m_socket->waitForReadyRead(1000);
    QByteArray ReceiverData = m_socket->readAll();
    qDebug() << ReceiverData;
    int emailNumbers = receiver->getEmailNum(ReceiverData);
    qDebug() << emailNumbers;

    for(int i=1;i<=emailNumbers;i++){
        QString send = "uidl "+QString::number(i)+"\r\n";
        m_socket->write(send.toUtf8());
        m_socket->waitForReadyRead(1000);
        QByteArray Data = m_socket->readLine();

        qDebug() << Data<<"\n\n";
        if(!receiver->isHaveEmail(Data)){
            send = "retr "+QString::number(i)+"\r\n";
            m_socket->write(send.toUtf8());
            m_socket->waitForReadyRead(4000);
            QByteArray emailData;
            while(m_socket->bytesAvailable()){
                emailData.append(m_socket->readAll());
                m_socket->waitForReadyRead(4000);
            }
            qDebug()<<emailData.size();
            qDebug()<<emailData<<"\n\n\n";
            receiver->analyseEmail(emailData);
        }
    }
    m_socket->write("quit\r\n");
    m_socket->waitForReadyRead(1000);
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
