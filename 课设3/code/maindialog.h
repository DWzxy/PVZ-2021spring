#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include<QDialog>
#include"overall.h"
#include"lawn.h"
#include"zombie.h"
#include"plant.h"
#include"store.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
class Dialog;
}
QT_END_NAMESPACE
class Lawn;
class Maindialog: public QDialog
{
    Q_OBJECT
public:
    Maindialog(QWidget* parent = 0);
    ~Maindialog();
public slots:
    void turn_to_day();//跳转到普通模式
    void turn_to_night();//跳转到挑战模式
    void turn_back();//跳转到选择界面
private:
    Ui::Dialog* ui;
    QMovie* background = new QMovie(":/else/mainlogo.png");
    Lawn* lawn;
    Start_screen* start_screen;
    Choose_screen* choose_screen;
};

#endif // MAINDIALOG_H
