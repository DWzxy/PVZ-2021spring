#include "maindialog.h"

#include <QApplication>
#include<QDialog>
#include<QDebug>
#include<QMainWindow>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Maindialog w;
    w.show();
    return a.exec();
}
