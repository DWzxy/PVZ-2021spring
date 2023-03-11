#pragma once
#include"overall.h"
using namespace std;
class Lawn;
class Game;
class Plant;
class Zombie: public Object
{
    friend class Plant;
    friend class Bullet;
    friend class Game;
    friend class Lawn;
    friend class Day_lawn;
    friend class Night_lawn;
    friend class Grid;
    friend class Cherry_bomb;
    friend class Wall_nut;
    friend class Snow_pea;
    friend class Squash;
    friend class Repeater;
    friend class Tall_nut;
    friend class Pumpkin;
    friend class Garlic;
    friend class Potato_mine;
    friend class Chomper;
    friend class Back_up;
protected:
    Zombie_type type;
    int attack;//攻击力
    int defence;//当前生命值
    double speed;//速度
    double rx;
    double ry;//绝对位置

    int attacking;//当前攻击时长

    int slowing;//当前余下的减速时间
    bool if_slowed;//是否已被冰冻
    int garlicing;//当前余下的被毒时间

    QMovie* background;
    QMovie* hit_movie;
public:
    //初始化
    Zombie(QWidget* parent = 0);
    //判断僵尸是否能攻击植物
    virtual bool can_attack();
    //僵尸攻击
    virtual void hit();
    //僵尸前进
    virtual void go();
    //死亡
    virtual void die();
    //减血
    void minus(int x);
    //冰冻状态
    void slow();
    //被毒状态
    void garlic(Game& game);
    //被炸
    void boom();
    ~Zombie();
};

class Ordinary: public Zombie
{
public:
    Ordinary(QWidget* parent = 0);
    void action();
};
class Flag: public Zombie
{
public:
    Flag(QWidget* parent = 0);
    void action();
};
class Conehead: public Zombie
{
    bool have_cone;
public:
    Conehead(QWidget* parent = 0);
    void action();
};
class Pole_vaulting: public Zombie
{
    friend class Chomper;
    friend class Potato_mine;
private:
    double speed2;
    bool has_jump;
    int jump_time;
    Plant* target;
public:
    Pole_vaulting(QWidget* parent = 0);
    void action();
    void jump();
    bool can_jump();
    void die();
};
class Bucket: public Zombie
{
    bool have_bucket;
public:
    Bucket(QWidget* parent = 0);
    void action();
};
class Newspaper: public Zombie
{
private:
    double speed2;
    bool angry;//是否已发疯
    int angry_time;//延迟时间
public:
    Newspaper(QWidget* parent = 0);
    void action();
    void die();
};
class Screen_door: public Zombie
{
    friend class Bullet;
private:
    bool have_door;//是否还有门
public:
    Screen_door(QWidget* parent = 0);
    void action();
};
class Back_up;
class Dancing: public Zombie
{
    friend class Grid;
    friend class Back_up;
    friend class Game;
    friend class Zombie;
    friend class Bullet;
private:
    int first_time;//出场第一次召唤所需时间
    int flash_time;//召唤的灯光时长
    int state;//跳舞阶段
    int make_cooling;//已冷却的召唤时间
    int make_time;//召唤所需时间
    int flag;//能否移动
    Back_up* left;
    Back_up* right;
    Back_up* top;
    Back_up* bottom;//四只伴舞僵尸
public:
    Dancing(QWidget* parent = 0);
    void action(Game& game);
    //最大冰冻值
    int max_slowing();
    //判断是否可移动
    bool can_move(Game& game);
    //添加伴舞僵尸
    void add_back_up(Game& game);
    //检查伴舞僵尸是否缺少
    bool check(Game& game);
};
class Back_up: public Zombie
{
    friend class Dancing;
    friend class Grid;
    friend class Game;
    friend class Lawn;
    friend class Zombie;
    friend class Bullet;
private:
    Dancing* dancing;
    int direction;//方位
public:
    Back_up();
    void action(Game& game);
};
class Jack_in_the_box: public Zombie
{
private:
    int life_time;//存活时间
    int bomb_time;//爆炸持续时长

public:
    Jack_in_the_box();
    void action(Game& game);
};
class Catapult: public Zombie
{
private:
    int ball_num;//篮球数量
    int throw_time;//投掷的时间间隔
    int throw_cooling;
public:
    Catapult();
    void action(Game& game);
    int can_attack(Game& game);
};
