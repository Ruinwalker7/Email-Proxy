#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "addaccount.h"
namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = 0);
    ~mainWidget();

private:
    Ui::mainWidget *ui;
    void add();
};

#endif // MAINWIDGET_H
