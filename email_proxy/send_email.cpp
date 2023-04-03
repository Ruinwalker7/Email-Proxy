#include "send_email.h"
#include "ui_send_email.h"
#include<QtNetwork>

send_email::send_email(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send_email)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);

    /*下面是几种常用的信号，更多的信号可以查看QAbstractSocket和QIODevice文档*/
    connect(m_socket, &QTcpSocket::connected, this, [] () {
        qDebug() << "socket已连接";
    });

    connect(m_socket, &QTcpSocket::disconnected, this, [] () {
        qDebug() << "socket已断开连接";
    });

    connect(m_socket, &QTcpSocket::stateChanged, this, [] (QAbstractSocket::SocketState socketState) {
        qDebug() << "socket状态改变" << socketState;
    });

    connect(m_socket, &QTcpSocket::readyRead, this, [] () {
        qDebug() << "有数据可读";
    });

    sendEmail();
}

void send_email::sendEmail(){

    port = 25;
    m_socket->connectToHost("smpt.qq.com", port);

}

send_email::~send_email()
{
    delete ui;
}

void send_email::OpenSocket()
{
    m_socket->connectToHost(hostName, port);

}
