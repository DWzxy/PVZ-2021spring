#pragma once
#include"plant.h"
#include"zombie.h"
#include"store.h"
using namespace std;
class Lawn : public Object
{
    Q_OBJECT
    friend class Game;
    friend class Plant;
    friend class Grid;
    friend class Bullet;
    friend class Peashooter;
    friend class Sunflower;
    friend class Cherry_bomb;
    friend class Wall_nut;
    friend class Snow_pea;
    friend class Squash;
    friend class Repeater;
    friend class Jalapeno;
    friend class Tall_nut;
    friend class Pumpkin;
    friend class Garlic;
    friend class Threepeater;
    friend class Spikeweed;
    friend class Potato_mine;
    friend class Chomper;
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

    friend class Shovel;
    friend class Card;
    friend class Sun;
protected:
    int zombie_cooling;//生产单个僵尸的进度
    int zombie_cool_time;//生产僵尸的时间间隔
    int zombie_number;//当前一波僵尸数目
    int zombie_circle [ 21 ] [ 2 ];//普通模式生产僵尸的时间间隔与数目
    int whole_wave;//完整的一轮包含的时间间隔数目
    bool flag;//是否已出现摇旗僵尸

    int sun_cooling;//目前生产单个阳光进度
    int sun_circle;//生产阳光的间隔

    Plant* plant[whole_length][whole_width]; //植物列表
    Pumpkin* pumpkin[whole_length][whole_width];//南瓜头
    Object* weed[whole_width]; //小推车列表
    QList<Zombie*>zombie_list[whole_width];  //僵尸列表
    QList<Bullet*>bullet_list;  //子弹列表
    QList<Sun*>sun_list;  //阳光列表
    QList<Special*>special_list;//特殊效果列表
    QList<Card*>card_list;  //植物卡列表

    Shovel* shovel = new Shovel(this);//铲子
    Object* shovel_back = new Object(this); //铲子框
    Card* leave = new Card(this); //菜单键
    Object* leave_text = new Object(leave);
    Card* menu = new Card(this); //菜单
    Card* exit = new Card(this); //返回选择界面键
    Object* exit_text = new Object(exit);
    Card* back = new Card(this); //返回游戏键
    Object* back_text = new Object(back);

    int start_time;//最开始的暂停时间
    Lawn_type type;
    Lawn_state state;
    QMediaPlayer* media = new QMediaPlayer(this);
    QMediaPlayer* media2 = new QMediaPlayer(this);
    QMediaPlaylist* list = new QMediaPlaylist(this);
    Object* lose = new Object(this);

    Plant* now_plant; //当前选中的植物或铲子
    Card* now_card;//当前选中的植物卡

    QTimer* timer = new QTimer;

    int card_cooling;
    int card_cool_time;

public:
    explicit Lawn(QWidget* parent = 0);
    ~Lawn();
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    //初始化
    virtual void build() {}
    //产生阳光
    void make_sun();
    //产生僵尸
    void make_zombie();
    void make_card();
    virtual void buy(int x) {}
    virtual bool can_buy(Card* x)
    {
        return true;
    }
    void choose_plant();
signals:
    void turn_day();
    void turn_night();
    void turn_back();
public slots:
    virtual void action();
    void over();
};

class Start_screen: public Object
{
    Q_OBJECT
private:
    QMovie* background = new QMovie(":/else/popcap.jpg");
    Object* back = new Object(this);
    QPalette* palette = new QPalette;
    int life_time ;
    QTimer* timer = new QTimer;
    QMediaPlayer* media = new QMediaPlayer(this);
    QMediaPlaylist* list = new QMediaPlaylist(this);
public:
    Start_screen(QWidget* parent = 0);
    ~Start_screen();
    void mousePressEvent(QMouseEvent* event);
signals:
    void turn_back();
private slots:
    void clock();
};

class Choose_screen: public Object
{
    Q_OBJECT
private:
    QMovie* background = new QMovie(":/else/title.jpg");
    Object* day = new Object(this);
    Object* night = new Object(this);
    Object* day_card = new Object(this);
    Object* night_card = new Object(this);
    Object* day_text = new Object(day_card);
    Object* night_text = new Object(night_card);
    QMediaPlayer* media = new QMediaPlayer;
    QTimer* timer = new QTimer;
    int type;
public:
    Choose_screen(QWidget* parent = 0);
    ~Choose_screen();
    void mousePressEvent(QMouseEvent* event);
signals:
    void turn_to_day();
    void turn_to_night();
private slots:
    void action();
};

class Day_lawn: public Lawn
{
    Q_OBJECT
    friend class Lawn;
    friend class Sun;
    friend class Card;
private:
    QMovie* background = new QMovie(":/lawn/day.jpg");
    Frame* frame = new Frame(this); //植物栏
public:
    Day_lawn(QWidget* parent = 0);
    ~Day_lawn();
    void build();
    void buy(int x);
    bool can_buy(Card* x);
};

class Night_lawn: public Lawn
{
    Q_OBJECT
    friend class Lawn;
private:
    QMovie* background = new QMovie(":/lawn/night.jpg");
    Object* belt = new Object(this);
public:
    Night_lawn(QWidget* parent = 0);
    ~Night_lawn();
    void build();
};
