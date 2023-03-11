#pragma once
#include"overall.h"
using namespace std;
class Game;
class Lawn;
class Zombie;
class Bullet: public Object
{
    friend class Game;
    friend class Zombie;
protected:
    Bullet_type type;//子弹种类
    int x;
    int y;//绝对位置
    int attack;//攻击力
    int speed;//速度

    Lawn* lawn;
    QMovie* background;
public:
    //初始化
    Bullet(int x, int y, QWidget* parent = 0);
    void action();
    void slow(Zombie* x);
    void unslow(Zombie* x);
    ~Bullet();
};
class Pea_bullet: public Bullet
{
public:
    Pea_bullet(int x, int y, QWidget* parent = 0);
};
class Snow_bullet: public Bullet
{
public:
    Snow_bullet(int x, int y, QWidget* parent = 0);
};
class Fire_bullet: public Bullet
{
public:
    Fire_bullet(int x, int y, QWidget* parent = 0);
};

class Plant: public Object
{
    friend class Bullet;
    friend class Store;
    friend class Game;
    friend class Grid;
    friend class Lawn;
    friend class Zombie;
    friend class Ordinary;
    friend class Flag;
    friend class Conehead;
    friend class Pole_vaulting;
    friend class Bucket;
    friend class Newspaper;
    friend class Dancing;
    friend class Back_up;
    friend class Jack_in_the_box;
    friend class Catapult;
    friend class Card;
protected:
    int defence;//现有生命值
    int x;
    int y;//相对位置
    int rx;
    int ry;//绝对位置
    int price;//价格

    Lawn* lawn;
public:
    Plant_type type;//种类
    //初始化
    Plant(QWidget* parent = 0);
    virtual void action();
    //默认判断射手攻击范围内是否有僵尸
    virtual bool can_attack();
    void set_pos(int x, int y);
    void minus(int x);
    ~Plant();
};
class Shovel: public Plant
{
private:
    QMovie* background = new QMovie(":/store/shovel.png");
public:
    Shovel(QWidget* parent = 0);
    void mousePressEvent(QMouseEvent* event);
};

class Peashooter: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
    int attack_cooling;//当前已冷却的攻击时间
    int attack_time;//攻击间隔时间
    QMovie* background = new QMovie(":/plant/peashooter.gif");
    //时间间隔单位均为0.1秒
public:
    Peashooter(QWidget* parent = 0);
    void action();
};

class Sunflower: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
    int make_sun;//生产阳光数
    int sun_circle;//生产阳光间隔
    int sun_cooling;//目前阳光冷却时间
    QMovie* background = new QMovie(":/plant/sunflower.gif");
public:
    Sunflower(QWidget* parent = 0);
    void action();
};
class Cherry_bomb: public Plant
{
    Q_OBJECT
    friend class Grid;
    friend class Lawn;
private:
    int attack;//攻击力
    int life_time;//生命周期
    QMovie* background = new QMovie(":/plant/cherry_bomb.gif");
public:
    Cherry_bomb(QWidget* parent = 0);
    void action();
private slots:

};
class Wall_nut: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
    int state;
    QMovie* background = new QMovie(":/plant/wall_nut.gif");
public:
    Wall_nut(QWidget* parent = 0);
    void action();

};
class Potato_mine: public Plant
{
    Q_OBJECT
    friend class Grid;
    friend class Lawn;
private:
    int rest_time;//准备时间
    int attack;//攻击力
    QMovie* background = new QMovie(":/plant/potato_mine.gif");
public:
    Potato_mine(QWidget* parent = 0);
    void action();
};
class Snow_pea: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
    int attack_cooling;//当前已冷却的攻击时间
    int attack_time;//攻击间隔时间
    //时间间隔单位均为0.1秒
    QMovie* background = new QMovie(":/plant/snow_pea.gif");
public:
    Snow_pea(QWidget* parent = 0);
    void action();
};
class Chomper: public Plant
{
    Q_OBJECT
    friend class Grid;
    friend class Lawn;
private:
    int attack_time;
    int rest_time;
    int attack;
    Zombie* target;
    QMovie* background = new QMovie(":/plant/chomper.gif");
public:
    Chomper(QWidget* parent = 0);
    void action();
};
class Repeater: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
    int attack_cooling;
    int first ;//第一颗离上一颗的时间
    int second ;//第二颗离上一颗的时间
    QMovie* background = new QMovie(":/plant/repeater.gif");
public:
    Repeater(QWidget* parent = 0);
    void action();
};
class Squash: public Plant
{
    Q_OBJECT
    friend class Grid;
    friend class Lawn;
private:
    int life_time;//从发现僵尸到攻击的时间
    int attack_time;//攻击效果持续时间
    int attack;//攻击力
    QMovie* background = new QMovie(":/plant/squash.gif");
public:
    Squash(QWidget* parent = 0);
    void action();
};
class Threepeater: public Plant
{
private:
    int attack_cooling;
    int attack_time;
    QMovie* background = new QMovie(":/plant/threepeater.gif");
public:
    Threepeater(QWidget* parent = 0);
    void action();
    bool can_attack();
};
class Jalapeno: public Plant
{
private:
    int life_time;
    int bomb_time;
    int attack;
    QMovie* background = new QMovie(":/plant/jalapeno.gif");
public:
    Jalapeno(QWidget* parent = 0);
    void action();
};
class Spikeweed: public Plant
{
private:
    int attack;
    int attack_cooling;
    int attack_time;
public:
    Spikeweed(QWidget* parent = 0);
    void action();
};
class Torchwood: public Plant
{
    QMovie* background = new QMovie(":/plant/torchwood.gif");
public:
    Torchwood(QWidget* parent = 0);
    void action();
};
class Tall_nut: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
    int state;
    QMovie* background = new QMovie(":/plant/tall_nut1.gif");
public:
    Tall_nut(QWidget* parent = 0);
    void action();
};
class Pumpkin: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
    int state;
    bool cover;//里面是否有植物
    QMovie* background = new QMovie(":/plant/pumpkin.gif");
public:
    Pumpkin(QWidget* parent = 0);
    void action();
};
class Garlic: public Plant
{
    friend class Grid;
    friend class Lawn;
private:
public:
    Garlic(QWidget* parent = 0);
    void action();
};
