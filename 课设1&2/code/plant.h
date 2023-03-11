#pragma once
#include<string>
#include"overall.h"
using namespace std;
class Bullet {
	friend class Game;
	friend class Zombie;
protected:
	Bullet_type type;//子弹种类
	int color;//颜色
	int x;
	int y;//绝对位置
	int attack;//攻击力
	int speed;//速度
public:
	//初始化
	Bullet( int x , int y );
};
class Pea_bullet:public Bullet{
public:
	Pea_bullet( int x , int y );
};
class Snow_bullet:public Bullet{
public:
	Snow_bullet( int x , int y );
};
class Fire_bullet:public Bullet{
public:
	Fire_bullet( int x , int y );
};
class Plant {
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
protected:
	string name;//名称
	Plant_type type;//种类
	int color;//当前颜色
	int origin_color;//原始颜色
	int high_light;//被攻击时的颜色
	int blood;//防御力
	int defence;//现有生命值
	int cost_sun;//价格
	int cooling;//当前已冷却时间
	int cool_time;//冷却时间
	int x;
	int y;//相对位置

	bool can_jump;//能否被跳过
	int eating;//被吃阶段
public:
	//初始化
	Plant();
	virtual void action( Game& game );
	//判断射手攻击范围内是否有僵尸
	bool shooter_can_attack( Lawn& lawn );
	//是否可跳过
	bool can_be_jump();
	//被吃的闪烁
	void shine(Lawn&lawn);
};
class Peashooter:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int attack_cooling;//当前已冷却的攻击时间
	int attack_time;//攻击间隔时间
	//时间间隔单位均为0.1秒
public:
	Peashooter();
	void action( Game& game );
};
class Sunflower:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int make_sun;//生产阳光数
	int start_sun_circle;//向日葵第一轮阳光生产时间
	bool if_start;//是否已进行第一轮生产
	int sun_circle;//生产阳光间隔
	int sun_cooling;//目前阳光冷却时间
	int sun_shine_time;//闪烁时长
public:
	Sunflower();
	void action( Game& game );
	//产生阳光时的闪烁
	void sun_shine( Game& game );
};
class Cherry_bomb:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int life_time;//从种下到爆炸的时间
	int bomb_time;//爆炸持续时间
	int attack;//攻击力
public:
	Cherry_bomb();
	void action( Game& game );
};
class Wall_nut:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Wall_nut();
	void action( Game& game );
};
class Potato_mine:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int rest_time;//准备时间
	int bomb_time;//爆炸时长
	int attack;//攻击力
public:
	Potato_mine();
	void action( Game& game );
};
class Snow_pea:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int attack_cooling;//当前已冷却的攻击时间
	int attack_time;//攻击间隔时间
	//时间间隔单位均为0.1秒
	int bullet_type;
	//子弹种类
public:
	Snow_pea();
	void action( Game& game );
};
class Chomper:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int rest_time;
	int attack;
public:
	Chomper();
	void action( Game& game );
};
class Repeater:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int attack_cooling;
	int first ;//第一颗离上一颗的时间
	int second ;//第二颗离上一颗的时间
	int bullet_type;
public:
	Repeater();
	void action( Game& game );
};
class Squash:public Plant{
	friend class Grid;
	friend class Lawn;
private:
	int life_time;//从发现僵尸到攻击的时间
	int squash_time;//攻击效果持续时间
	int attack;//攻击力
public:
	Squash();
	void action( Game& game );
};
class Threepeater:public Plant{
private:
	int attack_cooling;
	int attack_time;
public:
	Threepeater();
	void action( Game& game );
	bool can_attack( Lawn& lawn );
};
class Jalapeno:public Plant{
private:
	int life_time;
	int bomb_time;
	int attack;
public:
	Jalapeno();
	void action( Game& game );
};
class Spikeweed:public Plant{
private:
	int attack;
	int attack_cooling;
	int attack_time;
public:
	Spikeweed();
	void action( Game& game );
};
class Torchwood:public Plant{
public:
	Torchwood();
	void action( Game& game );
};
class Tall_nut:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Tall_nut();
	void action( Game& game );
};
class Pumpkin:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Pumpkin();
	void action( Game& game );
};
class Garlic:public Plant{
	friend class Grid;
	friend class Lawn;
private:
public:
	Garlic();
	void action( Game& game );
};
