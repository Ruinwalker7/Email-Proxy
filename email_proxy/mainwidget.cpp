#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "qtoolbar.h"
#include "send_email.h"

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    send_email *email = new send_email();
    ui->tabWidget->addTab(email, QString("发送邮件"));
    ui->tabWidget->setTabsClosable(true);
    connect(ui->add,&QPushButton::clicked,this,&mainWidget::add);
}


void mainWidget::add()
{
    addAccount *adda = new addAccount();
    adda->show();
}

mainWidget::~mainWidget()
{
    delete ui;
}
