#include"lawn.h"
#include"zombie.h"
#include"overall.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
class Game;

Lawn::Lawn(QWidget* parent): Object(parent)
{
    zombie_cooling = 0;//生产单个僵尸的进度
    whole_wave = 14;
    flag = 0;

    zombie_circle [ 0 ] [ 0 ] = 0;
    zombie_circle [ 1 ] [ 0 ] = 1000;
    zombie_circle [ 2 ] [ 0 ] = 2500;
    zombie_circle [ 3 ] [ 0 ] = 4000;
    zombie_circle [ 4 ] [ 0 ] = 5500;
    zombie_circle [ 5 ] [ 0 ] = 7000;
    zombie_circle [ 6 ] [ 0 ] = 8500;
    zombie_circle [ 7 ] [ 0 ] = 10000;
    zombie_circle [ 8 ] [ 0 ] = 11500;
    zombie_circle [ 9 ] [ 0 ] = 13000;
    zombie_circle [ 10 ] [ 0 ] = 14500;
    zombie_circle [ 11 ] [ 0 ] = 16000;
    zombie_circle [ 12 ] [ 0 ] = 17500;
    zombie_circle [ 13 ] [ 0 ] = 18250;
    zombie_circle [ 14 ] [ 0 ] = 19000;
    zombie_circle [ 0 ] [ 1 ] = 1;
    zombie_circle [ 1 ] [ 1 ] = 1;
    zombie_circle [ 2 ] [ 1 ] = 1;
    zombie_circle [ 3 ] [ 1 ] = 1;
    zombie_circle [ 4 ] [ 1 ] = 2;
    zombie_circle [ 5 ] [ 1 ] = 2;
    zombie_circle [ 6 ] [ 1 ] = 3;
    zombie_circle [ 7 ] [ 1 ] = 3;
    zombie_circle [ 8 ] [ 1 ] = 3;
    zombie_circle [ 9 ] [ 1 ] = 4;
    zombie_circle [ 10 ] [ 1 ] = 4;
    zombie_circle [ 11 ] [ 1 ] = 4;
    zombie_circle [ 12 ] [ 1 ] = 6;
    zombie_circle [ 13 ] [ 1 ] = 6;
    zombie_circle [ 14 ] [ 1 ] = 9;

    resize(2800, 1200);

    sun_cooling = 0;
    sun_circle = 275 + rand() % 200;//5.5-10.5秒掉落一个阳光
    start_time = 160;
    zombie_cooling = 0;
    zombie_cool_time = 900;
    zombie_number = 1;
    state = normal;

    now_plant = NULL;
    now_card = NULL;
    for (int i = 0; i < whole_length; i++) {
        for (int j = 0; j < whole_width; j++) {
            plant[i][j] = NULL;
            pumpkin[i][j] = NULL;
        }
    }

    leave->setGeometry(1830, 0, 200, 70);
    leave->setScaledContents(true);
    leave->setMovie(new QMovie(":/else/button.png"));
    leave->movie()->start();
    leave->setCursor(Qt::PointingHandCursor);
    leave->plant_type = Plant_type::menu;
    leave->show();
    leave->raise();
    leave->front->hide();

    leave_text->setGeometry(0, 0, 200, 70);
    leave_text->setText("菜单");
    leave_text->setAlignment(Qt::AlignCenter);
    leave_text->setFont(QFont("SimHei", 22));
    leave_text->show();
    leave_text->raise();

    shovel_back->setGeometry(grass_left + 1150, 0, plant_width, plant_width);
    shovel_back->setMovie(new QMovie(":/store/shovel_back.png"));
    shovel_back->movie()->start();
    shovel_back->setScaledContents(true);
    shovel_back->show();
    shovel_back->raise();
    shovel->raise();

    menu->resize(824, 966);
    menu->setScaledContents(true);
    menu->setMovie(new QMovie(":/else/tomb.png"));
    menu->move((grass_left + grass_right) / 2 - menu->width() / 2,
               (grass_top + grass_bottom) / 2 - menu->height() / 2);
    menu->movie()->start();
    menu->hide();

    back->resize(720, 200);
    back->move(menu->pos().x() + 70, menu->pos().y() + 760);
    back->setScaledContents(true);
    back->setMovie(new QMovie(":/else/choice.png"));
    back->movie()->start();
    back->setCursor(Qt::PointingHandCursor);
    back->plant_type = Plant_type::back;
    back->hide();

    back_text->setGeometry(0, 0, back->width(), back->height());
    back_text->setScaledContents(true);
    back_text->setText("返回游戏");
    back_text->setAlignment(Qt::AlignCenter);
    back_text->setFont(QFont("SimHei", 50));
    back_text->hide();

    exit->resize(470, 150);
    exit->move(menu->pos().x() + 180, menu->pos().y() + 580);
    exit->setScaledContents(true);
    exit->setMovie(new QMovie(":/else/button.png"));
    exit->movie()->start();
    exit->setCursor(Qt::PointingHandCursor);
    exit->plant_type = Plant_type::leave;
    exit->hide();

    exit_text->setGeometry(0, 0, exit->width(), exit->height());
    exit_text->setScaledContents(true);
    exit_text->setText("返回主界面");
    exit_text->setAlignment(Qt::AlignCenter);
    exit_text->setFont(QFont("SimHei", 40));
    exit_text->hide();

    lose->resize(1128, 936);
    lose->setScaledContents(true);
    lose->move((grass_right - grass_left) / 2 - menu->width() / 2,
               (grass_bottom + grass_top) / 2 - menu->height() / 2);
    lose->setMovie(new QMovie(":/else/lose.png"));
    lose->movie()->start();
    lose->hide();

    for (int i = 0; i < whole_width; i++) {
        weed[i] = new Object(this);
        weed[i]->resize(213, 171);
        weed[i]->setMovie(new QMovie(":/else/weed.gif"));
        weed[i]->setScaledContents(true);
        weed[i]->move(grass_left - weed[i]->width(), grass_top + i * single_width);
        weed[i]->movie()->start();
        weed[i]->show();
    }
}
void Lawn::mouseMoveEvent(QMouseEvent* event)
{
    //   qDebug() << event->x() << " " << event->y();
    if (now_plant != NULL) {
        if (now_plant->type == Plant_type::shovel) {
            now_plant->move(max(0, event->x() - 30), max(0, event->y() - 87));
        } else {
            now_plant->move(max(0, event->x() - 78), max(0, event->y() - 87));
        }
        now_plant->raise();
    }
}
void Lawn::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton || start_time) return;
    if (state == Lawn_state::over) emit turn_back();

    int x = get_x_num(event->x()), y = get_y_num(event->y());
    if (now_plant != NULL && now_plant->type == Plant_type::shovel) {
        x = now_plant->get_x(), y = now_plant->get_y();
    }
    if (x < 0 || x >= whole_length || y < 0 || y >= whole_width) {
        if (now_plant != NULL) {
            if (now_plant->type == Plant_type::shovel) {
                now_plant->move(grass_left + 1170, 20);
            } else {
                delete now_plant;
            }
        }
        now_plant = NULL;
        return;
    } else if (now_plant != NULL) {
        if (now_plant->type == Plant_type::shovel) {
            if (plant[x][y] != NULL) {
                QSound::play(":/music/plant.wav");
                delete plant[x][y];
                plant[x][y] = NULL;
            } else if (pumpkin[x][y] != NULL) {
                QSound::play(":/music/plant.wav");
                delete pumpkin[x][y];
                pumpkin[x][y] = NULL;
            }
            now_plant->move(grass_left + 1170, 20);
        } else {
            if ((now_plant->type != Plant_type::pumpkin && plant[x][y] != NULL)
                || (now_plant->type == Plant_type::pumpkin && pumpkin[x][y] != NULL)) {
                delete now_plant;
            } else {
                buy(now_plant->price);
                QSound::play(":/music/plant.wav");
                if (type == night) now_card->alive = 0;
                else now_card->cooling = 0;
                now_plant->set_pos(x, y);
                now_plant->move(now_plant->rx, now_plant->ry);
                if (now_plant->type == Plant_type::pumpkin) {
                    pumpkin[x][y] = (Pumpkin*)now_plant;
                } else {
                    plant[x][y] = now_plant;
                    now_plant->movie()->jumpToFrame(0);
                    if (now_plant->type == potato_mine) {
                        delete now_plant->movie();
                        now_plant->setMovie(new QMovie(":/plant/potato_mine_preparing.gif"));
                        now_plant->movie()->setScaledSize(QSize(144, 120));
                        now_plant->setAlignment(Qt::AlignCenter);
                        now_plant->movie()->start();
                    }
                }
                if (now_plant->type == tall_nut)
                    now_plant->move(now_plant->pos().x(), now_plant->pos().y() - 50);
            }
        }
        now_plant = NULL;
    }
}
void Lawn::make_sun()
{
    sun_cooling++;
    if (sun_cooling == sun_circle) {
        sun_cooling = 0;
        sun_circle = 275 + rand() % 200;
        sun_list.push_back(new Sun(this));
    }
}
void Lawn::make_card()
{
    if (card_list.size() == 11) return;
    card_cooling++;
    if (card_cooling == card_cool_time) {
        card_cooling = 0;
        Card* now = NULL;
        int num = 0;
        while (now == NULL) {
            num = rand() % 19;
            if (num == 5) now = new Peashooter_card(this);
            else if (num == 6) continue;
            else if (num == 7) now = new Cherry_bomb_card(this);
            else if (num == 8) now = new Wall_nut_card(this);
            else if (num == 9) now = new Potato_mine_card(this);
            else if (num == 10) now = new Snow_pea_card(this);
            else if (num == 11) now = new Chomper_card(this);
            else if (num == 12) now = new Repeater_card(this);
            else if (num == 13) now = new Squash_card(this);
            else if (num == 14) now = new Torchwood_card(this);
            else if (num == 15) now = new Tall_nut_card(this);
            else if (num == 16)now = new Pumpkin_card(this);
            else if (num == 17) now = new Threepeater_card(this);
            else if (num == 18)now = new Jalapeno_card(this);
        }
        now->x = grass_left + belt_length - card_width;
        now->y = 17;
        now->setGeometry(now->x, now->y, card_length, card_width);
        card_list.append(now);
    }
}
void Lawn::action()
{
    if (state == pause || state == Lawn_state::over) return;

    if (state == Lawn_state::lose) {
        if (start_time == 0) {
            state = Lawn_state::over;
            return;
        }
        start_time--;
        if (start_time >= 150) move(-(start_time - 150) * 4, 0);
        else {
            if (start_time == 149) {
                media2->setMedia(QUrl("qrc:/music/fail.mp3"));
                media2->setVolume(50);
                media2->play();
                lose->show();
                lose->raise();
            }
        }
        return;
    }

    if (start_time) {
        start_time--;
        if (start_time == 110) {
            Special* now = new Special(1, this);
            now->setMovie(new QMovie(":/else/preparing.gif"));
            now->movie()->start();
            now->resize(510, 216);
            now->move((grass_left + grass_right) / 2 - now->width() / 2,
                      (grass_top + grass_bottom) / 2 - now->height() / 2);
            now->show();
            special_list.push_back(now);
        }
        if (start_time == 0) {
            if (type == day)list->addMedia
                (QUrl("qrc:/music/day.mp3"));
            else list->addMedia
                (QUrl("qrc:/music/night.MP3"));
            list->setPlaybackMode(QMediaPlaylist::Loop);
            //"D:/useful/program/QT/Plants_vs_Zombies/music/start.mp3"
            media->setPlaylist(list);
            media->setVolume(50);
            media->play();
        }
        return;
    }

    if (type == day) make_sun();
    else make_card();

    make_zombie();

    for (int i = 0; i < card_list.size();) {
        if (type == day) card_list[i]->action(), i++; //普通模式冷却卡片
        else {
            Card* now = card_list[i];
            if (now->alive == 0) {
                delete now;
                card_list.removeAt(i);
            } else {
                int x = now->pos().x();
                if (i == 0) {
                    if (x >= 25 + grass_left) now->x -= 5;
                } else {
                    if (x >= card_list[i - 1]->pos().x() +
                        card_length + card_gap) now->x -= 5;
                }
                now->move(now->x, now->y);
                i++;
            }
        }//挑战模式移动卡片
    }

    for (int i = 0; i < whole_width; i++) {
        for (int j = 0; j < whole_length; j++) {
            Plant* now = plant[j][i];
            if (now != NULL) {
                if (now->alive == 0) {
                    delete now;
                    plant[j][i] = NULL;
                } else {
                    now->action();
                    now->raise();
                }
            }
            Pumpkin* cnt = pumpkin[j][i];
            if (cnt != NULL) {
                if (cnt->alive == 0) {
                    delete cnt;
                    pumpkin[j][i] = NULL;
                } else {
                    cnt->action();
                    cnt->raise();
                }
            }
        }

        for (int j = 0; j < zombie_list[i].size();) {
            Zombie* now = zombie_list[i][j];
            if (now->alive == 0) {
                delete now;
                zombie_list[i].removeAt(j);
            } else {
                now->action();
                now->raise();
                j++;
            }
        }

        if (weed[i] == NULL) continue;
        if (weed[i]->alive == 0) {
            if (weed[i]->pos().x() > grass_right + single_length) {
                delete weed[i];
                weed[i] = NULL;
            } else {
                weed[i]->move(weed[i]->pos().x() + 20, weed[i]->pos().y());
                weed[i]->raise();
                for (int j = 0; j < zombie_list[i].size(); j++) {
                    Zombie* now = zombie_list[i][j];
                    if (now->rx + now->width() / 3 <=
                        weed[i]->pos().x() + weed[i]->width() + 30 &&
                        now->rx + now->width() / 3 >=
                        weed[i]->pos().x() + weed[i]->width() - 30) {
                        now->minus(1000000);
                    }
                }
            }
        } else {
            for (int j = 0; j < zombie_list[i].size(); j++) {
                Zombie* now = zombie_list[i][j];
                if (now->rx + now->width() / 3 <= grass_left) {
                    weed[i]->alive = 0;
                    media2->setMedia(QUrl("qrc:/music/weed.mp3"));
                    media2->setVolume(75);
                    media2->play();
                }
            }
        }
    }

    for (int i = 0; i < bullet_list.size();) {
        if (bullet_list[i]->alive == 0) {
            delete bullet_list[i];
            bullet_list.removeAt(i);
        } else {
            bullet_list[i]->action();
            bullet_list[i]->raise();
            i++;
        }
    }

    for (int i = 0; i < special_list.size();) {
        if (special_list[i]->alive == 0) {
            delete special_list[i];
            special_list.removeAt(i);
        } else {
            special_list[i]->action();
            special_list[i]->raise();
            i++;
        }
    }

    for (int i = 0; i < sun_list.size();) {
        if (sun_list[i]->alive == 0) {
            delete sun_list[i];
            sun_list.removeAt(i);
        } else {
            sun_list[i]->action();
            sun_list[i]->raise();
            i++;
        }
    }

    if (now_plant != NULL) now_plant->raise();
}
void Lawn::over()
{
    state = Lawn_state::lose;
    media->stop();
    QSound::play(":/music/scary.wav");
    start_time = 250;
}
//产生僵尸
void Lawn::make_zombie()
{
    zombie_cooling++;
    if (type == day && zombie_circle [ 0 ] [ 1 ] <= whole_wave) {
        int num = zombie_circle [ 0 ] [ 1 ];
        if (zombie_cooling < zombie_circle [ num ] [ 0 ]) {
            return;
        }
        srand(time(NULL));
        if (num == whole_wave) {
            if (!flag) {
                flag = 1;
                int cnt = rand() % whole_width;
                Flag* new_zombie = new Flag(this);
                new_zombie->rx = grass_right + rand() % 200;
                new_zombie->ry = grass_top + single_width * cnt - new_zombie->height() / 3.5;
                zombie_list[cnt].append(new_zombie);
            }
            zombie_cooling = 0;
            zombie_number = 6;
        }
        if (num == 1) {
            media2->setMedia(QUrl("qrc:/music/wave.wav"));
            media2->setVolume(50);
            media2->play();
        }
        zombie_circle [ 0 ] [ 1 ]++;
        for (int k = 0; k < zombie_circle [ num ] [ 1 ]; k++) {
            int cnt = rand() % whole_width;
            Zombie* now = NULL;
            while (now == NULL) {
                int type = rand() % 100;
                if (type < 13) {
                    now = new Ordinary(this);
                } else if (type < 43 && num >= 4) {
                    now = new Conehead(this);
                } else if (type < 53 && num >= 8) {
                    now = new Pole_vaulting(this);
                } else if (type < 73 && num >= 11) {
                    now = new Bucket(this);
                } else if (type < 83 && num >= 11) {
                    now = new Newspaper(this);
                } else if (type < 90 && num >= 13) {
                    now = new Screen_door(this);
                }
            }
            now->rx = grass_right + rand() % 200;
            now->ry = grass_top + single_width * cnt - now->height() + single_width;
            now->move(now->rx, now->ry);
            zombie_list[cnt].append(now);
        }
    } else {
        if (zombie_cooling < zombie_cool_time)  return;
        zombie_cooling = 0;
        for (int k = 0; k < zombie_number; k++) {
            int cnt = rand() % whole_width;
            Zombie* now = NULL;
            while (now == NULL) {
                int type = rand() % 6;
                if (type == 0)now = new Ordinary(this);
                else if (type == 1) now = new Conehead(this);
                else if (type == 2) now = new Pole_vaulting(this);
                else if (type == 3) now = new Bucket(this);
                else if (type == 4) now = new Newspaper(this);
                else if (type == 5) now = new Screen_door(this);
            }
            now->rx = grass_right + rand() % 400;
            now->ry = grass_top + single_width * cnt  - now->height() + single_width;
            now->move(now->rx, now->ry);
            zombie_list[cnt].append(now);
        }
        if (type == night || zombie_number < 15) zombie_number++;
    }
}
void Lawn::choose_plant()
{
    bool book[20] = {};
    int type = rand() % 13;

    Card* new_card = new Sunflower_card(this);
    new_card->set_pos(0);
    card_list.append(new_card);

    for (int i = 1; i < 10; i++) {
        while (book[type] == 1) type = rand() % 13;
        book[type] = 1;
        if (type == 0) {
            new_card = new Peashooter_card(this);
        } else if (type == 1) {
            new_card = new Jalapeno_card(this);
        } else if (type == 2) {
            new_card = new Cherry_bomb_card(this);
        } else if (type == 3) {
            new_card = new Wall_nut_card(this);
        } else if (type == 4) {
            new_card = new Potato_mine_card(this);
        } else if (type == 5) {
            new_card = new Snow_pea_card(this);
        } else if (type == 6) {
            new_card = new Chomper_card(this);
        } else if (type == 7) {
            new_card = new Repeater_card(this);
        } else if (type == 8) {
            new_card = new Squash_card(this);
        } else if (type == 9) {
            new_card = new Torchwood_card(this);
        } else if (type == 10) {
            new_card = new Tall_nut_card(this);
        } else if (type == 11) {
            new_card = new Pumpkin_card(this);
        } else if (type == 12) {
            new_card = new Threepeater_card(this);
        }
        new_card->set_pos(i);
        card_list.append(new_card);
    }
}
Lawn::~Lawn()
{
    delete leave->movie();
    delete shovel_back->movie();
    delete menu->movie();
    delete back->movie();
    delete exit->movie();
    delete lose->movie();

    delete shovel;
    delete shovel_back;
    delete leave ;
    delete menu;
    delete exit ;
    delete back ;
    delete media;
    delete media2 ;
    delete list ;
    delete lose;
    delete timer;

    for (int i = 0; i < whole_length; i++) {
        for (int j = 0; j < whole_width; j++) {
            delete plant[i][j];
            delete pumpkin[i][j];
        }
    }

    for (int i = 0; i < whole_width; i++) delete weed[i];
    for (int i = 0; i < whole_width; i++) {
        while (zombie_list[i].size()) zombie_list[i].removeAt(0);
    }
    while (bullet_list.size()) bullet_list.removeAt(0);
    while (sun_list.size()) sun_list.removeAt(0);
    while (special_list.size()) special_list.removeAt(0);
    while (card_list.size()) card_list.removeAt(0);
}

Start_screen::Start_screen(QWidget* parent): Object(parent)
{
    setGeometry(0, 0, 1600, 1200);
    setScaledContents(true);
    setMovie(background);
    background->start();
    show();

    life_time = 175;
    //    list->addMedia(QUrl("D:/useful/program/QT/Plants_vs_Zombies/music/start.mp3"));
    list->addMedia(QUrl("qrc:/music/start.MP3"));
    list->setPlaybackMode(QMediaPlaylist::Loop);
    //"D:/useful/program/QT/Plants_vs_Zombies/music/start.mp3"
    media->setPlaylist(list);

    media->setVolume(50);
    media->play();


    back->setGeometry(0, 0, 1600, 1200);
    back->setAutoFillBackground(true);
    palette->setColor(QPalette::Background, QColor(0, 0, 0, 255));
    back->setPalette(*palette);
    back->show();

    timer->setInterval(20);
    connect(timer, SIGNAL(timeout()), this, SLOT(clock()));
    timer->start();
}
void Start_screen::clock()
{
    if (!life_time) return;
    life_time--;
    if (life_time <= 150 && life_time >= 100) {
        palette->setColor(QPalette::Background,
                          QColor(0, 0, 0, (int)((life_time - 100) * 5.1)));
        back->setPalette(*palette);
    } else if (life_time < 50) {
        palette->setColor(QPalette::Background,
                          QColor(0, 0, 0, (int)((50 - life_time) * 5.1)));
        back->setPalette(*palette);
    }
    if (life_time == 0) {
        delete movie();
        delete back;
        delete palette;
        setMovie(new QMovie(":/else/start_screen.png"));
        movie()->start();
    }
}
Start_screen::~Start_screen()
{
    delete timer;
    delete media;
    delete list;
}
void Start_screen::mousePressEvent(QMouseEvent* event)
{
    if (life_time) return;
    if (event->button() != Qt::LeftButton) return;
    emit turn_back();
}

Choose_screen::Choose_screen(QWidget* parent): Object(parent)
{
    setMovie(background);
    background->setScaledSize(QSize(1600, 1200));
    setGeometry(0, 0, 1600, 1200);
    background->start();
    show();

    day->setGeometry(300, 430, 200, 200);
    day->setMovie(new QMovie(":/else/day.png"));
    day->setScaledContents(true);
    day->movie()->start();
    day->show();

    night->setGeometry(1100, 430, 200, 200);
    night->setMovie(new QMovie(":/else/night.png"));
    night->setScaledContents(true);
    night->movie()->start();
    night->show();

    day_card->setGeometry(287, 700, 226, 82);
    day_card->setScaledContents(true);
    day_card->setMovie(new QMovie(":/else/button.png"));
    day_card->movie()->start();
    day_card->setCursor(Qt::PointingHandCursor);
    day_card->show();
    day_card->raise();

    night_card->setGeometry(1087, 700, 226, 82);
    night_card->setScaledContents(true);
    night_card->setMovie(new QMovie(":/else/button.png"));
    night_card->movie()->start();
    night_card->setCursor(Qt::PointingHandCursor);
    night_card->show();
    night_card->raise();

    day_text->setGeometry(0, 0, day_card->width(), day_card->height());
    day_text->setText("普通模式");
    day_text->setAlignment(Qt::AlignCenter);
    day_text->setFont(QFont("SimHei", 20));
    day_text->show();
    day_text->raise();

    night_text->setGeometry(0, 0, day_card->width(), day_card->height());
    night_text->setText("挑战模式");
    night_text->setAlignment(Qt::AlignCenter);
    night_text->setFont(QFont("SimHei", 20));
    night_text->show();
    night_text->raise();

    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(action()));
}
Choose_screen::~Choose_screen()
{
    delete background;
    delete day;
    delete night;
    delete day_card;
    delete night_card;
    delete media;
    delete timer;
}
void Choose_screen::mousePressEvent(QMouseEvent* event)
{
    if (timer->isActive()) return;

    if (QRect(287, 700, 226, 82).contains(event->pos())) {
        media->setMedia(QUrl("qrc:/music/laugh.mp3"));
        media->setVolume(50);
        media->play();
        timer->start();
        type = 0;
    }
    if (QRect(1087, 700, 226, 82).contains(event->pos())) {
        media->setMedia(QUrl("qrc:/music/laugh.mp3"));
        media->setVolume(50);
        media->play();
        timer->start();
        type = 1;
    }
}
void Choose_screen::action()
{
    if (media->position() == media->duration()) {
        if (type == 0) emit turn_to_day();
        else emit turn_to_night();
    }
}

Day_lawn::Day_lawn(QWidget* parent): Lawn(parent)
{
    type = day;

    background->setScaledSize(QSize(2800, 1200));
    setGeometry(-440, 0, 2800, 1200);
    setMovie(background);
    background->start();
    show();

    build();
    connect(this, SIGNAL(turn_back()), parent, SLOT(turn_back()));

    timer->setInterval(20);
    connect(timer, SIGNAL(timeout()), this, SLOT(action()));
    timer->start();
}
Day_lawn::~Day_lawn()
{
    delete background;
    delete frame;
}
void Day_lawn::build()
{
    choose_plant();

    /*   Zombie* new_zombie = new Pole_vaulting(this);
       new_zombie->rx = grass_right;
       new_zombie->ry = grass_top  - new_zombie->height() / 3.5;
       new_zombie->move(new_zombie->rx, new_zombie->ry);
       zombie_list[0].append(new_zombie);*/
}
void Day_lawn::buy(int x)
{
    frame->sun_number -= x;
    frame->now_sun->setText(QString::number(frame->sun_number));
}
bool Day_lawn::can_buy(Card* x)
{
    return frame->sun_number >= x->cost_sun && x->cooling == x->cool_time;
}

Night_lawn::Night_lawn(QWidget* parent): Lawn(parent)
{
    type = night;
    card_cooling = 100;
    card_cool_time = 200;
    zombie_cooling = 600;

    background->setScaledSize(QSize(2800, 1200));
    setGeometry(-440, 0, 2800, 1200);
    setMovie(background);
    background->start();
    show();

    belt->setMovie(new QMovie(":/store/belt.png"));
    belt->setGeometry(grass_left, 0, belt_length, plant_width);
    belt->setScaledContents(true);
    belt->movie()->start();
    belt->show();
    belt->raise();

    build();
    connect(this, SIGNAL(turn_back()), parent, SLOT(turn_back()));

    timer->setInterval(20);
    connect(timer, SIGNAL(timeout()), this, SLOT(action()));
    timer->start();
}
void Night_lawn::build()
{
    /*   Zombie* new_zombie = new Newspaper(this);
       new_zombie->rx = grass_right;
       new_zombie->ry = grass_top + single_width * 2 - new_zombie->height() / 3.5;
       new_zombie->move(new_zombie->rx, new_zombie->ry);
       zombie_list[2].append(new_zombie);*/
}
Night_lawn::~Night_lawn()
{
    delete background;
    delete belt->movie();
    delete belt;
}
