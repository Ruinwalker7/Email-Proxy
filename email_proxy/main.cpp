#include "mainwindow.h"
#include <QApplication>
#include "send_email.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    send_email w;
    w.show();

    return a.exec();
}
