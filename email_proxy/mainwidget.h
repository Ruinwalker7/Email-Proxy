#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "addaccount.h"
#include "QList"
#include "QHash"

//struct account{
//    QString user,password;
//};

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = 0);
    void updateAccounts();
    QHash<QString,QString> accounts;
    ~mainWidget();

private:
    Ui::mainWidget *ui;
    void on_tabWidget_tabCloseRequested(int index);
    void add();
};

#endif // MAINWIDGET_H
