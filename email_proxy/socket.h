#ifndef SOCKET_H
#define SOCKET_H
#include "QTcpSocket"

class socket
{
public:
    socket();
    socket(QString user,QString password);
    bool sendEmail();
    bool checkAccount();
    QString WaitAndReadData();
    ~socket();
private:
    QString m_UserName,m_Password,stmp_addr;
    QTcpSocket *m_socket;

};

#endif // SOCKET_H
