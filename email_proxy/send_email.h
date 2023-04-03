#ifndef SEND_EMAIL_H
#define SEND_EMAIL_H

#include <QWidget>
#include <windows.h>
#include <stdio.h>
#include <WinSock.h>
#include <iostream>
#include "QTcpSocket"

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

private:
    Ui::send_email *ui;
    QTcpSocket *m_socket;
    void OpenSocket();
    QString hostName;
    quint16 port;
};

#endif // SEND_EMAIL_H
