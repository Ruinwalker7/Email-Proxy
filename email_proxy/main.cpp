#include "mainwidget.h"
#include <QApplication>
#include "send_email.h"
//#include "controlfiles.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QString controlFiles::dir = QCoreApplication::applicationDirPath();
    mainWidget w;
    w.show();
    return a.exec();
}
