#ifndef ADDACCOUNT_H
#define ADDACCOUNT_H

#include <QWidget>

namespace Ui {
class addAccount;
}

class addAccount : public QWidget
{
    Q_OBJECT

public:
    explicit addAccount(QWidget *parent = 0);
    ~addAccount();

private:
    Ui::addAccount *ui;
    QString user;
    QString password;
    void addUser();
};

#endif // ADDACCOUNT_H
