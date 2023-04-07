#ifndef EMAILRECEIVE_H
#define EMAILRECEIVE_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class EmailReceive;
}

class EmailReceive : public QWidget
{
    Q_OBJECT

public:
    explicit EmailReceive(QWidget *parent = 0);
    ~EmailReceive();
    void setUserName(QString username);
    bool isHaveEmail(QByteArray socketReceive);
    void analyseEmail(QByteArray emailDetail);
    int getEmailNum(QByteArray socketReceive);

private:
    Ui::EmailReceive *ui;
    QString _userName;

};

#endif // EMAILRECEIVE_H
