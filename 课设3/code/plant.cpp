#include"plant.h"
#include"overall.h"
#include"lawn.h"
#include<iostream>
using namespace std;
//初始化
Bullet::Bullet(int p, int q, QWidget* parent): Object(parent)
{
    x = p;
    y = q;
    attack = 20;
    speed = 14;
    move(x, y);
    lawn = (Lawn*)parent;
}
void Bullet::action()
{
    int now = (y - grass_top) / single_width;
    Zombie* cnt = NULL;
    for (int i = 0; i < lawn->zombie_list[now].size(); i++) {
        Zombie* tem = lawn->zombie_list[now][i];
        if (tem->rx + tem->width() / 3 < x - 10
            || tem->rx + tem->width() / 3 > x + 50) continue;
        if (cnt == NULL) cnt = tem;
        else if (tem->rx < cnt->rx) cnt = tem;
    }
    if (cnt != NULL) {
        if (type == fire) QSound::play(":/music/fire.wav");
        else if (cnt->type == bucket || cnt->type == screen_door)
            QSound::play(":/music/iron.wav");
        else QSound::play(":/music/peahit.wav");
        if (cnt->defence > 0) {
            cnt->minus(attack);
            if (cnt->defence <= 0)cnt->die();
        }

        if (type == snow) slow(cnt);
        if (type == fire) unslow(cnt);
        alive = 0;
    } else {
        if (x < grass_left + whole_length * single_length) {
            if (get_x() < whole_length) {
                Plant* now = lawn->plant[get_x()][get_y()];
                if (now != NULL && now->type == torchwood && type != fire) {
                    int cnt = x - get_x() * single_length - grass_left;
                    if (cnt <= 20 || cnt > 34) {
                        x += speed;
                        move(x, y);
                        return;
                    }
                    if (type == pea) {
                        alive = 0;
                        lawn->bullet_list.push_back(new Fire_bullet
                                                    (pos().x() + speed, pos().y(), lawn));
                    } else if (type == snow) {
                        alive = 0;
                        lawn->bullet_list.push_back(new Pea_bullet
                                                    (pos().x() + speed, pos().y(), lawn));
                    }
                } else {
                    x += speed;
                    move(x, y);
                }
            } else {
                x += speed;
                move(x, y);
            }
        } else alive = 0;
    }
}
void Bullet::slow(Zombie* zombie)
{
    zombie->slowing = 501;
    if (zombie->type == dancing) {
        if (((Dancing*) zombie)->left != NULL)
            ((Dancing*) zombie)->left->slowing = 501;
        if (((Dancing*) zombie)->right != NULL)
            ((Dancing*) zombie)->right->slowing = 501;
        if (((Dancing*) zombie)->top != NULL)
            ((Dancing*) zombie)->top->slowing = 501;
        if (((Dancing*) zombie)->bottom != NULL)
            ((Dancing*) zombie)->bottom->slowing = 501;
    }
    if (zombie->type == back_up) {
        ((Back_up*) zombie)->dancing->slowing = 501;
        if (((Back_up*) zombie)->dancing->left != NULL)
            ((Back_up*) zombie)->dancing->left->slowing = 501;
        if (((Back_up*) zombie)->dancing->right != NULL)
            ((Back_up*) zombie)->dancing->right->slowing = 501;
        if (((Back_up*) zombie)->dancing->top != NULL)
            ((Back_up*) zombie)->dancing->top->slowing = 501;
        if (((Back_up*) zombie)->dancing->bottom != NULL)
            ((Back_up*) zombie)->dancing->bottom->slowing = 501;
    }//舞王与伴舞一同减速
}
void Bullet::unslow(Zombie* zombie)
{
    if (zombie->slowing) zombie->slowing = 1;
    if (zombie->type == dancing) {
        if (((Dancing*) zombie)->left != NULL)
            ((Dancing*) zombie)->left->slowing = 1;
        if (((Dancing*) zombie)->right != NULL)
            ((Dancing*) zombie)->right->slowing = 1;
        if (((Dancing*) zombie)->top != NULL)
            ((Dancing*) zombie)->top->slowing = 1;
        if (((Dancing*) zombie)->bottom != NULL)
            ((Dancing*) zombie)->bottom->slowing = 1;
    }
    if (zombie->type == back_up) {
        ((Back_up*) zombie)->dancing->slowing = 1;
        if (((Back_up*) zombie)->dancing->left != NULL)
            ((Back_up*) zombie)->dancing->left->slowing = 1;
        if (((Back_up*) zombie)->dancing->right != NULL)
            ((Back_up*) zombie)->dancing->right->slowing = 1;
        if (((Back_up*) zombie)->dancing->top != NULL)
            ((Back_up*) zombie)->dancing->top->slowing = 1;
        if (((Back_up*) zombie)->dancing->bottom != NULL)
            ((Back_up*) zombie)->dancing->bottom->slowing = 1;
    }//舞王与伴舞一同恢复速度
}
Bullet::~Bullet()
{
    delete movie();
}
Pea_bullet::Pea_bullet(int x, int y, QWidget* parent): Bullet(x, y, parent)
{
    type = pea;
    resize(120, 70);
    background = new QMovie(":/plant/pea.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Snow_bullet::Snow_bullet(int x, int y, QWidget* parent) : Bullet(x, y, parent)
{
    type = snow;
    resize(120, 70);
    background = new QMovie(":/plant/ice_pea.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}
Fire_bullet::Fire_bullet(int x, int y, QWidget* parent) : Bullet(x, y, parent)
{
    type = fire;
    attack = 40;
    resize(120, 70);
    background = new QMovie(":/plant/fire_pea.gif");
    setMovie(background);
    setScaledContents(true);
    movie()->start();
    show();
    raise();
}

Plant::Plant(QWidget* parent) : Object(parent)
{
    lawn = (Lawn*)parent;
}
void Plant::set_pos(int X, int Y)
{
    x = X;
    y = Y;
    rx = grass_left + x * single_length + single_length / 2 - width() / 2;
    ry = grass_top + y * single_width;
}
void Plant::action() {}
//判断射手攻击范围内是否有僵尸
bool Plant::can_attack()
{
    for (int i = 0; i < lawn->zombie_list[y].size(); i++) {
        Zombie* now = lawn->zombie_list[y][i];
        if (now->rx + now->width() / 2 >= rx && now->rx + now->width() / 2  < grass_left +
            whole_length * single_length)return true;
    }
    return false;
}
void Plant::minus(int x)
{
    defence -= x;
    if (defence <= 0) alive = 0;
}
Plant::~Plant()
{
    delete movie();
}

Shovel::Shovel(QWidget* parent): Plant(parent)
{
    type = shovel;
    setGeometry(grass_left + 1170, 20, 116, 125);
    background->setScaledSize(QSize(93, 100));
    setAlignment(Qt::AlignCenter);
    setMovie(background);
    background->start();
    show();
    raise();
}
void Shovel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton || lawn->start_time) return;
    if (lawn->state == pause) return;

    if (lawn->now_plant == NULL) {
        lawn->now_plant = this;
        this->raise();
    } else {
        lawn->mousePressEvent(event);
    }
}

Peashooter::Peashooter(QWidget* parent): Plant(parent)
{
    type = peashooter;
    defence = 300;
    attack_cooling = 20;
    attack_time = 70;
    price = 100;

    resize(157, 175);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Sunflower::Sunflower(QWidget* parent): Plant(parent)
{
    type = sunflower;
    defence = 300;
    make_sun = 25;//每次生产25阳光
    sun_circle = 275;//第一次只需7.5秒，后续每隔24秒生产一个阳光
    sun_cooling = 0;
    price = 50;

    resize(157, 175);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Cherry_bomb::Cherry_bomb(QWidget* parent): Plant(parent)
{
    type = cherry_bomb;
    defence = 30000;
    attack = 1800;
    life_time = 25;
    price = 150;

    resize(178, 136);
    setMovie(background);
    setScaledContents(true);
    movie()->setSpeed(75);
    background->start();
    show();
    raise();
}
Wall_nut::Wall_nut(QWidget* parent): Plant(parent)
{
    type = wall_nut;
    defence = 4000;
    state = 0;
    price = 50;

    resize(152, 177);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Potato_mine::Potato_mine(QWidget* parent): Plant(parent)
{
    type = potato_mine;
    defence = 300;
    rest_time = 750;
    attack = 1800;
    price = 25;

    resize(148, 176);
    setMovie(background);
    background->setScaledSize(QSize(148, 106));
    background->start();
    show();
    raise();
}
Snow_pea::Snow_pea(QWidget* parent): Plant(parent)
{
    type = snow_pea;
    defence = 300;
    attack_cooling = 20;
    attack_time = 70;
    price = 175;

    resize(157, 175);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Chomper::Chomper(QWidget* parent): Plant(parent)
{
    type = chomper;
    defence = 300;
    attack_time = 0;
    rest_time = 0;
    attack = 1800;
    price = 150;

    resize(180, 180);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Repeater::Repeater(QWidget* parent): Plant(parent)
{
    type = repeater;
    defence = 300;
    attack_cooling = 10;
    first = 60;
    second = 10;
    price = 200;

    resize(170, 170);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Squash::Squash(QWidget* parent): Plant(parent)
{
    type = squash;
    defence = 30000;
    life_time = 0;
    attack_time = 0;
    attack = 1800;
    price = 50;

    resize(146, 170);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Threepeater::Threepeater(QWidget* parent): Plant(parent)
{
    type = threepeater;
    defence = 300;
    attack_cooling = 20;
    attack_time = 70;
    price = 325;

    resize(146, 160);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Jalapeno::Jalapeno(QWidget* parent): Plant(parent)
{
    type = jalapeno;
    defence = 30000;
    life_time = 11;
    bomb_time = 11;
    attack = 1800;

    resize(136, 178);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Spikeweed::Spikeweed(QWidget* parent): Plant(parent)
{
    type = spikeweed;
    defence = 300;
    attack = 20;
    attack_time = 7;
    attack_cooling = 7;
}
Torchwood::Torchwood(QWidget* parent): Plant(parent)
{
    type = torchwood;
    defence = 300;
    price = 175;

    resize(146, 174);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Tall_nut::Tall_nut(QWidget* parent): Plant(parent)
{
    type = tall_nut;
    defence = 8000;
    price = 125;
    state = 0;

    resize(166, 238);
    setMovie(background);
    setScaledContents(true);
    background->start();
    show();
    raise();
}
Pumpkin::Pumpkin(QWidget* parent): Plant(parent)
{
    type = pumpkin;
    defence = 4000;
    price = 125;
    state = 0;
    cover = 0;

    resize(240, 240);
    setMovie(background);
    movie()->setScaledSize(QSize(230, 170));
    background->start();
    show();
    raise();
}
Garlic::Garlic(QWidget* parent): Plant(parent)
{
    type = garlic;
    defence = 400;
}

//豌豆射手行动
void Peashooter::action()
{
    if (attack_cooling < attack_time) {
        attack_cooling++;
    }
    if (attack_cooling == attack_time) {
        if (!can_attack()) {
            attack_cooling -= rand() % 20;
            return;
        }
        attack_cooling = 0;
        QSound::play(":/music/pea.wav");
        lawn->bullet_list.push_back(
            new Pea_bullet(x * single_length + grass_left + 40,
                           y *  single_width  + grass_top + 20, lawn));
    }
}
//向日葵行动
void Sunflower::action()
{
    sun_cooling++;
    if (sun_cooling == sun_circle) {
        sun_cooling = 0;
        sun_circle = 1200;
        Sun* now = new Sun(lawn);
        lawn->sun_list.push_back(now);
        now->move(rx + single_length / 2, ry + single_length / 2);
        now->position = rx + single_length / 2;
        now->height = ry + single_length / 2 + 40;
    }
}
//樱桃炸弹行动
void Cherry_bomb::action()
{
    if (movie()->currentFrameNumber() < movie()->frameCount() - 1) return;
    alive = 0;
    QSound::play(":/music/bomb.wav");
    Special* now = new Special(1, lawn);
    now->setMovie(new QMovie(":/plant/boom.gif"));
    now->resize(300, 300);
    now->move(pos().x() - 30, pos().y() - 30);
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);
    int now1 = max(0, y - 1), now2 = min(whole_width - 1, y + 1);
    for (int i = now1; i <= now2; i++) {
        for (int j = 0; j < lawn->zombie_list[i].size(); j++) {
            Zombie* now = lawn->zombie_list[i][j];
            if (now->get_x() >= x - 1 && now->get_x() <= x + 1) {
                now->minus(attack);
                now->boom();
            }
        }
    }
}
//坚果墙行动
void Wall_nut::action()
{
    if (state == 0 && defence <= 2667) {
        state = 1;
        delete movie();
        setMovie(new QMovie(":/plant/wall_nut_1.gif"));
        movie()->start();
    }
    if (state == 1 && defence <= 1333) {
        state = 2;
        delete movie();
        setMovie(new QMovie(":/plant/wall_nut_2.gif"));
        movie()->start();
    }
}
//土豆雷行动
void Potato_mine::action()
{
    if (rest_time) {
        rest_time--;
        if (rest_time == 0) {
            delete movie();
            resize(148, 176);
            setMovie(new QMovie(":/plant/potato_mine.gif"));
            movie()->setScaledSize(QSize(148, 106));
            setAlignment(Qt::AlignCenter);
            movie()->start();
        }
    }
    if (rest_time) return;
    bool flag = 0;
    for (int i = 0; i < lawn->zombie_list[y].size(); i++) {
        Zombie* now = lawn->zombie_list[y][i];
        if (now->type == pole_vaulting && ((Pole_vaulting*)now)->has_jump == 0)
            continue;
        if (now->get_x() == x) {
            flag = 1;
            now->minus(attack);
        }
    }
    if (flag) {
        QSound::play(":/music/potato_mine.wav");
        alive = 0;
        Special* now1 = new Special(30, lawn);
        now1->setMovie(new QMovie(":/plant/potato_mine_boom.gif"));
        now1->resize(196, 138);
        now1->move(pos().x() + 15, pos().y() + 20);
        now1->movie()->start();
        now1->show();

        Special* now2 = new Special(30, lawn);
        now2->setMovie(new QMovie(":/plant/potato_text.gif"));
        now2->resize(270, 81);
        now2->move(pos().x(), pos().y() + 50);
        now2->movie()->start();
        now2->show();

        lawn->special_list.push_back(now1);
        lawn->special_list.push_back(now2);
    }
}
//寒冰射手行动
void Snow_pea::action()
{
    if (attack_cooling < attack_time) {
        attack_cooling++;
    }
    if (attack_cooling == attack_time) {
        if (!can_attack()) {
            attack_cooling -= rand() % 20;
            return;
        }
        attack_cooling = 0;
        QSound::play(":/music/pea.wav");
        lawn->bullet_list.push_back(
            new Snow_bullet(x * single_length + grass_left + 40,
                            y *  single_width  + grass_top + 20, lawn));
    }
}
//食人花行动
void Chomper::action()
{
    if (attack_time) {
        attack_time--;
        if (attack_time == 0) {
            move(rx, ry);
            delete movie();
            if (rest_time == 0) {
                resize(180, 180);
                setMovie(new QMovie(":/plant/chomper.gif"));
                movie()->start();
            } else {
                resize(180, 180);
                setMovie(new QMovie(":/plant/chomper_preparing.gif"));
                movie()->start();
            }
        }
        if (attack_time == 25) {
            int cnt = target->rx + target->width() / 2 - rx;
            if (cnt >= 30 && target->type != pole_vaulting) {
                target->minus(attack);
                rest_time = 2250;
            }
        }
    }
    if (attack_time) return;
    if (rest_time) {
        rest_time--;
        if (rest_time == 0) {
            delete movie();
            resize(180, 180);
            setMovie(new QMovie(":/plant/chomper.gif"));
            movie()->start();
        }
    }
    if (rest_time) return;
    target = NULL;
    for (int i = 0; i < lawn->zombie_list[y].size(); i++) {
        Zombie* now = lawn->zombie_list[y][i];
        int dis = now->rx + now->width() / 2 - rx;
        if (dis < 30 || dis > single_length * 2)  continue;
        if (target == NULL || now->rx < target->rx) target = now;
    }
    if (target == NULL) return;
    delete movie();
    resize(260, 228);
    move(rx, ry - 48);
    setMovie(new QMovie(":/plant/chomperattack.gif"));
    movie()->setSpeed(50);
    movie()->start();
    raise();
    attack_time = 60;
}
//双发射手行动
void Repeater::action()
{
    if (attack_cooling < first + second) attack_cooling++;
    if (attack_cooling == first) {
        if (!can_attack()) {
            attack_cooling -= rand() % 20;
            return;
        }
        QSound::play(":/music/pea.wav");
        lawn->bullet_list.push_back(
            new Pea_bullet(x * single_length + grass_left + 40,
                           y *  single_width  + grass_top + 20, lawn));
    }
    if (attack_cooling == first + second) {
        if (!can_attack()) {
            attack_cooling -= rand() % 10;
            return;
        }
        attack_cooling = 0;
        QSound::play(":/music/pea.wav");
        lawn->bullet_list.push_back(
            new Pea_bullet(x * single_length + grass_left + 40,
                           y *  single_width  + grass_top + 20, lawn));
    }
}
//窝瓜行动
void Squash::action()
{
    if (attack_time) {
        attack_time--;
        if (attack_time == 35) {
            for (int i = 0; i < lawn->zombie_list[y].size(); i++) {
                Zombie* now = lawn->zombie_list[y][i];
                if (now->rx + now->width() / 2 > rx + width() / 2 - 80 &&
                    now->rx + now->width() / 2 < rx + width() / 2 + 80) now->minus(attack);
            }
        }
        if (attack_time == 0) alive = 0;
        return;
    }

    if (life_time) {
        life_time--;
        if (life_time == 0) {
            delete movie();
            setMovie(new QMovie(":/plant/squashattack.gif"));
            resize(200, 452);
            move(rx, ry - 250);
            movie()->start();
            raise();

            attack_time = 50;
        }
        return;
    }

    bool flag = 0;
    for (int i = 0; i < lawn->zombie_list[y].size(); i++) {
        Zombie* now = lawn->zombie_list[y][i];
        if (now->get_x() == x || now->get_x() == x + 1) flag = 1;
    }
    if (!flag) return;

    delete movie();
    setMovie(new QMovie(":/plant/squash_preparing.png"));
    resize(200, 180);
    move(rx - 20, ry);
    movie()->start();
    raise();
    life_time = 30;
    int cnt = rx + single_length * 3 / 2;
    for (int i = 0; i < lawn->zombie_list[y].size(); i++) {
        Zombie* now = lawn->zombie_list[y][i];
        if (now->get_x() != x && now->get_x() != x + 1) continue;
        cnt = min(cnt, (int)now->rx + now->width() / 2 - width() / 2);
    }
    rx = cnt;
}
//三线射手行动
void Threepeater::action()
{
    if (attack_cooling < attack_time) attack_cooling++;
    if (attack_cooling == attack_time) {
        if (!can_attack()) {
            attack_cooling -= rand() % 20;
            return;
        }
        attack_cooling = 0;
        QSound::play(":/music/pea.wav");
        lawn->bullet_list.push_back(
            new Pea_bullet(x * single_length + grass_left + 40,
                           y *  single_width  + grass_top + 20, lawn));
        if (y > 0) {
            lawn->bullet_list.push_back(
                new Pea_bullet(x * single_length + grass_left + 40,
                               (y - 1) *  single_width  + grass_top + 20, lawn));
        }
        if (y < whole_width - 1) {
            lawn->bullet_list.push_back(
                new Pea_bullet(x * single_length + grass_left + 40,
                               (y + 1) *  single_width  + grass_top + 20, lawn));
        }
    }
}
bool Threepeater::can_attack()
{
    if (Plant::can_attack()) return true;
    if (y > 0) {
        y--;
        if (Plant::can_attack()) {
            y++;
            return true;
        }
        y++;
    }
    if (y < whole_width - 1) {
        y++;
        if (Plant::can_attack()) {
            y--;
            return true;
        }
        y--;
    }
    return false;
}
//火爆辣椒行动
void Jalapeno::action()
{
    if (movie()->currentFrameNumber() < movie()->frameCount() - 1) return;
    alive = 0;
    QSound::play(":/music/bomb.wav");
    Special* now = new Special(1, lawn);
    now->setMovie(new QMovie(":/plant/jalafire.gif"));
    now->resize(whole_length * single_length + single_length / 2, single_width);
    now->move(grass_left, pos().y());
    now->movie()->start();
    now->show();
    lawn->special_list.push_back(now);
    for (int j = 0; j < lawn->zombie_list[y].size(); j++) {
        Zombie* now = lawn->zombie_list[y][j];
        now->minus(attack);
        now->boom();
    }
}
//地刺行动
void Spikeweed::action()
{
    /*  shine( game.lawn );
    if ( attack_cooling < attack_time ) attack_cooling++;
    if ( attack_cooling < attack_time )return;
    attack_cooling = 0;
    Grid* now = &game.lawn.grid_list[x][y];
    list<Zombie*>::iterator k;
    for ( k = now->zombie_list.begin();
          k != now->zombie_list.end(); k++ ){
        now->zombie_minus( ( *k ) , attack , game );
    }*/
}
//火炬树桩行动
void Torchwood::action()
{

}
//高坚果行动
void Tall_nut::action()
{
    if (state == 0 && defence <= 5334) {
        state = 1;
        delete movie();
        setMovie(new QMovie(":/plant/tall_nut2.gif"));
        movie()->start();
    }
    if (state == 1 && defence <= 2667) {
        state = 2;
        delete movie();
        setMovie(new QMovie(":/plant/tall_nut3.gif"));
        movie()->start();
    }
}
//南瓜头行动
void Pumpkin::action()
{
    if (state == 0 && cover == 0 && lawn->plant[x][y] != NULL) {
        cover = 1;
        delete movie();
        setMovie(new QMovie(":/plant/pumpkin1.gif"));
        movie()->setScaledSize(QSize(230, 170));
        movie()->start();
        raise();
    }

    if (state == 0 && cover == 1 && lawn->plant[x][y] == NULL) {
        cover = 0;
        delete movie();
        setMovie(new QMovie(":/plant/pumpkin.gif"));
        movie()->setScaledSize(QSize(230, 170));
        movie()->start();
        raise();
    }

    if (state == 0 && defence <= 2667) {
        state = 1;
        delete movie();
        setMovie(new QMovie(":/plant/pumpkin2.gif"));
        movie()->setScaledSize(QSize(230, 170));
        movie()->start();
    }
    if (state == 1 && defence <= 1333) {
        state = 2;
        delete movie();
        setMovie(new QMovie(":/plant/pumpkin3.gif"));
        movie()->setScaledSize(QSize(230, 170));
        movie()->start();
    }
}
//大蒜行动
void Garlic::action()
{
    //  shine( game.lawn );
}



