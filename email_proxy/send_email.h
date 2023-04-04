#ifndef SEND_EMAIL_H
#define SEND_EMAIL_H

#include <QWidget>
#include <stdio.h>
#include <iostream>
#include <socket.h>

namespace Ui {
class send_email;
}

class send_email : public QWidget
{
    Q_OBJECT

public:
    explicit send_email(QWidget *parent = 0);
    ~send_email();
    void sendEmail();
    void setUser(QString user,QString password);

private:
    socket* m_socket;
    Ui::send_email *ui;
    QString hostName;
    quint16 port;
    QByteArray  m_UserName;
    QByteArray  m_Password;
    QByteArray  sendIp;
    QByteArray  s_Title;
    QByteArray  s_Content;
};

#endif // SEND_EMAIL_H
