#include "maindialog.h"

Maindialog::Maindialog(QWidget* parent): QDialog(parent)
{
    setWindowIcon(QIcon(":/else/mainlogo.png"));
    resize(1600, 1200);
    start_screen = new Start_screen(this);
    choose_screen = NULL;
    lawn = NULL;
    connect(start_screen, SIGNAL(turn_back()), this, SLOT(turn_back()));
}
Maindialog::~Maindialog()
{
    delete ui;
    delete background;
    delete lawn;
    delete start_screen;
    delete choose_screen;
}
void Maindialog::turn_to_day()
{
    srand(time(NULL));
    delete choose_screen;
    choose_screen = NULL;
    delete lawn;
    lawn = new Day_lawn(this);
    connect(lawn, SIGNAL(turn_back()), this, SLOT(turn_back()));
}
void Maindialog::turn_to_night()
{
    srand(time(NULL));
    delete choose_screen;
    choose_screen = NULL;
    delete lawn;
    lawn = new Night_lawn(this);
    connect(lawn, SIGNAL(turn_back()), this, SLOT(turn_back()));
}
void Maindialog::turn_back()
{
    delete start_screen;
    start_screen = NULL;
    delete lawn;
    lawn = NULL;
    choose_screen = new Choose_screen(this);
    connect(choose_screen, SIGNAL(turn_to_day()), this, SLOT(turn_to_day()));
    connect(choose_screen, SIGNAL(turn_to_night()), this, SLOT(turn_to_night()));
}
