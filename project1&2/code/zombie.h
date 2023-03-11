#pragma once
#include<string>
using namespace std;
class Lawn;
class Back_up;
class Zombie {
	friend class Bullet;
	friend class Game;
	friend class Lawn;
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
	string name;//名称
	Zombie_type type;
	int attack;//攻击力
	int defence;//当前生命值
	int blood;//总生命值
	int speed;//速度（实际上是走完一格需要的时间）
	int speed_cooling;//当前行进完一格的进度
	int score;//击败获得的得分
	int x;
	int y;//相对位置
	int origin_color;//原本的颜色
	int color;//当前的颜色

	bool if_slowed;//是否正在减速
	int slowing;//当前余下的减速时间
	int garlicing;//当前余下的被毒时间
	bool can_jump;//能否跳过植物
public:
	//初始化
	Zombie( );
	//僵尸移动
	void move( Game& game );
	//僵尸攻击
	void hit( Game& game );
	//判断僵尸是否能攻击植物
	bool zombie_can_attack(Game&game);
	//僵尸行动
	virtual void action( Game& game );
	//冰冻状态
	void slow(Game&game);
	//被毒状态
	void garlic(Game&game);
};
class Ordinary:public Zombie{
public:
	Ordinary();
	void action( Game& game );
};
class Flag:public Zombie{
public:
	Flag();
	void action( Game& game );
};
class Conehead:public Zombie{
public:
	Conehead();
	void action( Game& game );
};
class Pole_vaulting:public Zombie{
private:
	string name2;
	int speed2;
public:
	Pole_vaulting();
	void action( Game& game );
	void jump( Game& game );
};
class Bucket:public Zombie{
public:
	Bucket();
	void action( Game& game );
};
class Newspaper:public Zombie{
private:
	string name2;
	int speed2;
	bool angry;//是否已发疯
public:
	Newspaper();
	void action( Game& game );
};
class Dancing:public Zombie{
	friend class Grid;
	friend class Back_up;
	friend class Game;
	friend class Zombie;
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
	Dancing();
	void action( Game& game );
	//最大冰冻值
	int max_slowing();
	//判断是否可移动
	bool can_move( Game& game );
	//添加伴舞僵尸
	void add_back_up( Game& game );
	//检查伴舞僵尸是否缺少
	bool check( Game& game );
};
class Back_up:public Zombie{
	friend class Dancing;
	friend class Grid;
	friend class Game;
	friend class Lawn;
	friend class Zombie;
private:
	Dancing* dancing;
	int direction;//方位
public:
	Back_up();
	void action( Game& game );
};
class Jack_in_the_box:public Zombie{
private:
	int life_time;//存活时间
	int bomb_time;//爆炸持续时长

public:
	Jack_in_the_box();
	void action( Game& game );
};
class Catapult:public Zombie{
private:
	int ball_num;//篮球数量
	int throw_time;//投掷的时间间隔
	int throw_cooling;
public:
	Catapult();
	void action( Game& game );
	int can_attack( Game& game );
};