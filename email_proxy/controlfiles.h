#ifndef CONTROLFILES_H
#define CONTROLFILES_H

#include "QCoreApplication"
#include "QList"
#include "QStringList"
class controlFiles
{
public:
    controlFiles();
    void saveUser(QString user,QString password);
    static QString dir;
    void updateAccount(QStringList *list);
private:

};

#endif // CONTROLFILES_H
