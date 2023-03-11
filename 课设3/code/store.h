#pragma once
#include"plant.h"
#include"overall.h"
using namespace std;
class Lawn;

class Card: public Object
{
    friend class Lawn;
    friend class Day_lawn;
    friend class Night_lawn;
    friend class Choose_screen;
protected:
    int x;
    int y;//坐标
    Plant_type plant_type;//植物种类
    Object* background = new Object(this);//图片
    int cost_sun;//价格
    int cooling;//当前已冷却时间
    int cool_time;//冷却时间
    QPalette* palette = new QPalette;
    Object* front = new Object(this);//未冷却的覆盖部分
public:
    Card(QWidget* parent = 0);
    void set_pos(int x);//放置到植物栏的对应位置
    void mousePressEvent(QMouseEvent* event);
    //重写鼠标点击函数
    bool is_card();//判断是否是真正的植物卡
    void action();
    ~Card();
};

class Frame: public Object
{
    Q_OBJECT
    friend class Lawn;
    friend class Day_lawn;
    friend class Night_lawn;
    friend class Card;
    friend class Sun;
    friend class Sunflower;
private:
    int action_num;
    int sun_number;
    Object* shovel_back;
    Object* now_sun = new Object(this);
    QTimer* timer = new QTimer;
public:
    Frame(QWidget* parent = 0);
    ~Frame();
private slots:
    void action();
};

class Leave: public Card
{
    Q_OBJECT
public:
    Leave(QWidget* parent = 0);
    ~Leave();
};

class Sun: public Object
{
    Q_OBJECT
    friend class Lawn;
    friend class Sunflower;
private:
    int position;
    int height;
    int speed;
    int speed_x;
    int speed_y;
    bool clicked;
    int life_time;
    QGraphicsOpacityEffect* visible = new QGraphicsOpacityEffect;
public:
    Sun(QWidget* parent = 0);
    ~Sun();
    void mousePressEvent(QMouseEvent* event);
    void action();
};

class Sunflower_card: public Card
{
    Q_OBJECT
private:
public:
    Sunflower_card(QWidget* parent = 0);
    ~Sunflower_card();
};

class Peashooter_card: public Card
{
    Q_OBJECT
private:
public:
    Peashooter_card(QWidget* parent = 0);
    ~Peashooter_card();
};

class Cherry_bomb_card: public Card
{
    Q_OBJECT
private:
public:
    Cherry_bomb_card(QWidget* parent = 0);
    ~Cherry_bomb_card();
};

class Wall_nut_card: public Card
{
    Q_OBJECT
private:
public:
    Wall_nut_card(QWidget* parent = 0);
    ~Wall_nut_card();
};

class Potato_mine_card: public Card
{
    Q_OBJECT
private:
public:
    Potato_mine_card(QWidget* parent = 0);
    ~Potato_mine_card();
};

class Snow_pea_card: public Card
{
    Q_OBJECT
private:
public:
    Snow_pea_card(QWidget* parent = 0);
    ~Snow_pea_card();
};

class Chomper_card: public Card
{
    Q_OBJECT
private:
public:
    Chomper_card(QWidget* parent = 0);
    ~Chomper_card();
};

class Repeater_card: public Card
{
    Q_OBJECT
private:
public:
    Repeater_card(QWidget* parent = 0);
    ~Repeater_card();
};

class Squash_card: public Card
{
private:
public:
    Squash_card(QWidget* parent = 0);
    ~Squash_card();
};

class Threepeater_card: public Card
{
private:
public:
    Threepeater_card(QWidget* parent = 0);
    ~Threepeater_card();
};

class Jalapeno_card: public Card
{
private:
public:
    Jalapeno_card(QWidget* parent = 0);
    ~Jalapeno_card();
};

class Torchwood_card: public Card
{
private:
public:
    Torchwood_card(QWidget* parent = 0);
    ~Torchwood_card();
};

class Tall_nut_card: public Card
{
private:
public:
    Tall_nut_card(QWidget* parent = 0);
    ~Tall_nut_card();
};

class Pumpkin_card: public Card
{
private:
public:
    Pumpkin_card(QWidget* parent = 0);
    ~Pumpkin_card();
};

class Gatling_card: public Card
{
private:
public:
    Gatling_card(QWidget* parent = 0);
    ~Gatling_card();
};
