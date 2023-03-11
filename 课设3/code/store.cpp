#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<iostream>
#include"store.h"
#include"lawn.h"
#include"overall.h"
using namespace std;
class Game;

Card::Card(QWidget* parent): Object(parent)
{
    front->setGeometry(0, 0, card_length, card_width);
    palette->setColor(QPalette::Background, QColor(0, 0, 0, 150));
    front->setAutoFillBackground(true);
    front->setPalette(*palette);
    front->hide();
}
void Card::set_pos(int z)
{
    x = grass_left + (z + 1) * (card_length + card_gap) + card_gap * 4;
    y = 15;
    setGeometry(x, y, card_length, card_width);
}
void Card::mousePressEvent(QMouseEvent* event)
{
    if (lawn->state == Lawn_state::over) return;
    if (event->button() != Qt::LeftButton || lawn->start_time) return;

    if (plant_type == menu) {
        lawn->state = pause;
        QSound::play(":/music/not_enough_sun.wav");
        lawn->media->pause();
        lawn->menu->show();
        lawn->menu->raise();
        lawn->back->show();
        lawn->back->raise();
        lawn->back_text->show();
        lawn->back_text->raise();
        lawn->exit->show();
        lawn->exit->raise();
        lawn->exit_text->show();
        lawn->exit_text->raise();
        return;
    }

    if (plant_type == back) {
        lawn->state = normal;
        lawn->media->play();
        lawn->menu->hide();
        lawn->back->hide();
        lawn->back_text->hide();
        lawn->exit->hide();
        lawn->exit_text->hide();
        return;
    }

    if (plant_type == leave) {
        lawn->emit turn_back();
        return;
    }

    if (lawn->state == pause) return;

    if (plant_type == rubbish) return;

    if (lawn->now_plant == NULL) {
        if (!lawn->can_buy(this)) {
            QSound::play(":/music/not_enough_sun.wav");
            if (lawn->type == day) {
                Day_lawn* now = ((Day_lawn*)lawn);
                if (now->frame->sun_number < cost_sun)now->frame->action_num = 20;
            }

        } else {
            if (plant_type == peashooter) {
                lawn->now_plant = new Peashooter(lawn);
            } else if (plant_type == sunflower) {
                lawn->now_plant = new Sunflower(lawn);
            } else if (plant_type == cherry_bomb) {
                lawn->now_plant = new Cherry_bomb(lawn);
            } else if (plant_type == wall_nut) {
                lawn->now_plant = new Wall_nut(lawn);
            } else if (plant_type == potato_mine) {
                lawn->now_plant = new Potato_mine(lawn);
            } else if (plant_type == snow_pea) {
                lawn->now_plant = new Snow_pea(lawn);
            } else if (plant_type == chomper) {
                lawn->now_plant = new Chomper(lawn);
            } else if (plant_type == repeater) {
                lawn->now_plant = new Repeater(lawn);
            } else if (plant_type == squash) {
                lawn->now_plant = new Squash(lawn);
            } else if (plant_type == torchwood) {
                lawn->now_plant = new Torchwood(lawn);
            } else if (plant_type == tall_nut) {
                lawn->now_plant = new Tall_nut(lawn);
            } else if (plant_type == pumpkin) {
                lawn->now_plant = new Pumpkin(lawn);
            } else if (plant_type == threepeater) {
                lawn->now_plant = new Threepeater(lawn);
            } else if (plant_type == jalapeno) {
                lawn->now_plant = new Jalapeno(lawn);
            } else {
                return;
            }
            lawn->now_plant->x = x - 30;
            lawn->now_plant->y = y ;
            lawn->now_plant->move(x - 30, y);
            lawn->now_card = this;
            lawn->now_plant->raise();
        }
    } else {
        delete lawn->now_plant;
        lawn->now_plant = NULL;
    }
}
bool Card::is_card()
{
    if (plant_type == shovel || plant_type == leave || plant_type == back
        || plant_type == menu || plant_type == rubbish) return false;
    return true;
}
void Card::action()
{
    if (cooling < cool_time) cooling++;
    front->resize(card_length, card_width * (1.0 - (double)cooling / cool_time));
    front->show();
    front->raise();
}
Card::~Card()
{
    delete background;
    delete palette;
    delete front;
}

Frame::Frame(QWidget* parent): Object(parent)
{
    setMovie(new QMovie(":/store/frame.png"));
    setGeometry(grass_left, 0, plant_length, plant_width);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
    sun_number = 50;
    now_sun->setGeometry(523 - grass_left, 113, 100, 36);
    now_sun->setAlignment(Qt::AlignCenter);
    now_sun->setText("50");
    now_sun->setFont(QFont("SimHei", 16));
    now_sun->show();
    now_sun->raise();
    action_num = 0;

    timer->setInterval(20);
    connect(timer, SIGNAL(timeout()), this, SLOT(action()));
    timer->start();
}
Frame::~Frame()
{
}
void Frame::action()
{
    if (action_num == 0) return;
    action_num--;
    QPalette now;
    if ((action_num / 2) & 1)now.setColor(QPalette::WindowText, Qt::red);
    else now.setColor(QPalette::WindowText, Qt::black);
    now_sun->setPalette(now);
}

Leave::Leave(QWidget* parent): Card(parent)
{
    setMovie(new QMovie(":/else/leave.png"));
    setGeometry(1900, 25, 120, 120);
    movie()->setScaledSize(QSize(120, 120));
    movie()->start();
    show();
    raise();
    cost_sun = 0;
}
Leave::~Leave()
{
}

Sun::Sun(QWidget* parent): Object(parent)
{
    setMovie(new QMovie(":/else/sun.gif"));
    position = grass_left + rand() % (single_length * (whole_length - 1));
    height = grass_top + single_width + rand() % (single_width * (whole_width - 2));
    setGeometry(position, grass_top, 150, 150);
    movie()->setScaledSize(QSize(150, 150));
    movie()->start();
    show();
    raise();
    speed = 4;
    clicked = 0;
    life_time = 450;
    visible->setOpacity(1);
    setGraphicsEffect(visible);
}
Sun::~Sun()
{
    delete movie();
}
void Sun::mousePressEvent(QMouseEvent* event)
{
    if (lawn->state == pause || lawn->state == Lawn_state::over) return;
    if (event->button() != Qt::LeftButton || lawn->start_time) return;

    clicked = 1;
    visible->setOpacity(1);
    speed_x = (pos().x() - 500) / 50, speed_y = (pos().y() - 63) / 50;
    raise();
    QSound::play(":/music/sun.wav");
}
void Sun::action()
{
    if (!clicked) {
        if (pos().y() < height) {
            move(pos().x(), pos().y() + speed);
        } else {
            life_time--;
            if (life_time <= 150) {
                if (life_time % 15 == 0) {
                    if (life_time / 15 & 1) {
                        visible->setOpacity(1);
                    } else {
                        visible->setOpacity(0.3);
                    }
                }
            }
            if (life_time == 0) {
                alive = 0;
            }
        }
    } else {
        if (pos().x() > 500 && pos().y() > 63) {
            move(pos().x() - speed_x, pos().y() - speed_y);
        } else {
            ((Day_lawn*)lawn)->frame->sun_number += 25;
            ((Day_lawn*)lawn)->frame->now_sun->
            setText(QString::number(((Day_lawn*)lawn)->frame->sun_number));
            alive = 0;
        }
        if (pos().x() < 600 && pos().y() < 163) {
            visible->setOpacity((pos().x() - 500) / 100.0);
        }
    }
    raise();
}

Sunflower_card::Sunflower_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/sunflower.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = sunflower;
    show();
    raise();
    cost_sun = 50;
    cooling = 0;
    cool_time = 375;
}
Sunflower_card::~Sunflower_card()
{
}

Peashooter_card::Peashooter_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/peashooter.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = peashooter;
    show();
    raise();
    cost_sun = 100;
    cooling = 0;
    cool_time = 375;
}
Peashooter_card::~Peashooter_card()
{
}

Cherry_bomb_card::Cherry_bomb_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/cherry_bomb.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = cherry_bomb;
    show();
    raise();
    cost_sun = 150;
    cooling = 0;
    cool_time = 1500;
}
Cherry_bomb_card::~Cherry_bomb_card()
{
}

Wall_nut_card::Wall_nut_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/wall_nut.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = wall_nut;
    show();
    raise();
    cost_sun = 50;
    cooling = 0;
    cool_time = 1500;
}
Wall_nut_card::~Wall_nut_card()
{
}

Potato_mine_card::Potato_mine_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/potato_mine.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = potato_mine;
    show();
    raise();
    cost_sun = 25;
    cooling = 0;
    cool_time = 1500;
}
Potato_mine_card::~Potato_mine_card()
{
}

Snow_pea_card::Snow_pea_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/snow_pea.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = snow_pea;
    show();
    raise();
    cost_sun = 175;
    cooling = 0;
    cool_time = 375;
}
Snow_pea_card::~Snow_pea_card()
{
}

Chomper_card::Chomper_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/chomper.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = chomper;
    show();
    raise();
    cost_sun = 150;
    cooling = 0;
    cool_time = 375;
}
Chomper_card::~Chomper_card()
{
}

Repeater_card::Repeater_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/repeater.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = repeater;
    show();
    raise();
    cost_sun = 200;
    cooling = 0;
    cool_time = 375;
}
Repeater_card::~Repeater_card()
{
}

Squash_card::Squash_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/squash.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = squash;
    show();
    raise();
    cost_sun = 50;
    cooling = 0;
    cool_time = 1500;
}
Squash_card::~Squash_card()
{
}

Threepeater_card::Threepeater_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/threepeater.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = threepeater;
    show();
    raise();
    cost_sun = 325;
    cooling = 0;
    cool_time = 375;
}
Threepeater_card::~Threepeater_card()
{
}

Jalapeno_card::Jalapeno_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/jalapeno.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = jalapeno;
    show();
    raise();
    cost_sun = 125;
    cooling = 0;
    cool_time = 2500;
}
Jalapeno_card::~Jalapeno_card()
{
}

Torchwood_card::Torchwood_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/torchwood.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = torchwood;
    show();
    raise();
    cost_sun = 175;
    cooling = 0;
    cool_time = 375;
}
Torchwood_card::~Torchwood_card()
{
}

Tall_nut_card::Tall_nut_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/tall_nut.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = tall_nut;
    show();
    raise();
    cost_sun = 125;
    cooling = 0;
    cool_time = 1500;
}
Tall_nut_card::~Tall_nut_card()
{
}

Pumpkin_card::Pumpkin_card(QWidget* parent): Card(parent)
{
    background->setMovie(new QMovie(":/store/pumpkin.jpg"));
    background->movie()->setScaledSize(QSize(card_length, card_width));
    background->movie()->start();
    background->show();
    plant_type = pumpkin;
    show();
    raise();
    cost_sun = 125;
    cooling = 0;
    cool_time = 1500;
}
Pumpkin_card::~Pumpkin_card()
{
}
